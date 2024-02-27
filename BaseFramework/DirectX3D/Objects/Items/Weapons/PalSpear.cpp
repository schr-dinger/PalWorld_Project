#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.01f, 0.01f, 0.01f }; // ũ�� �⺻���� 1
                                      // ���߿� ũ�Ⱑ �ٲ��� �ϸ� �ͼ� �����ϰ�
    transform->Rot().x += XM_PIDIV2;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //ũ�� �⺻���� 1.0
    collider->Pos() = {};            //��ġ �⺻�� : �θ� ��ġ
}

PalSpear::~PalSpear()
{
    delete collider;

}

void PalSpear::Update()
{
    //��Ȱ��ȭ �߿��� �� ������
    if (!transform->Active()) return;

    time += DELTA; // �ð� ����� ���� ������ ����

    //if (time > LIFE_SPAN)
    //    transform->SetActive(false);

    
    downForce += gravi * DELTA;

    Vector3 tmp = (direction * speed + down * downForce) * DELTA;

    //transform->Pos() += direction * speed * DELTA;
    transform->Pos() += tmp;

    if (transform->Pos().y <= terrain->GetHeight(transform->GlobalPos()))
    {
        downForce *= -1;
    }
    speed -= DELTA * 3;
    if (speed <= 0.0f)
    {
        speed = 0.0f;
        //if (transform->Pos().y <= terrain->GetHeight(transform->GlobalPos()))
        //{
        //    transform->SetActive(false);
        //    speed = 10.0f;
        //}
    }

    collider->UpdateWorld();
}

void PalSpear::Render()
{
    collider->Render();
}

void PalSpear::GUIRender()
{
    ImGui::Text("Down : %f", downForce);
}

void PalSpear::Throw(Vector3 pos, Vector3 dir)
{
    //Ȱ��ȭ
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //���⿡ �°� ��(=Ʈ������) ȸ�� ����
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2; //���� ���� + �� ���鿡 ���� ����
                                                          //���� ���� 90�� ���ư� �־���
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           �� ������ ȣ���� �ٲ��ִ� �Լ�

    time = 0; //����ð� ����
}
