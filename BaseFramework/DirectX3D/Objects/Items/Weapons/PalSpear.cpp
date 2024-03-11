#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.01f, 0.01f, 0.01f }; // ũ�� �⺻���� 1
                                      // ���߿� ũ�Ⱑ �ٲ��� �ϸ� �ͼ� �����ϰ�
    transform->Rot().x += XM_PIDIV2;

    terrain = nullptr;
    pal = nullptr;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //ũ�� �⺻���� 1.0
    collider->Pos() = {};            //��ġ �⺻�� : �θ� ��ġ

    state = State::THROW;
}

PalSpear::~PalSpear()
{
    delete collider;

}

void PalSpear::Update()
{
    //��Ȱ��ȭ �߿��� �� ������
    if (!transform->Active()) return;

    switch (state)
    {
    case PalSpear::State::THROW:
        StateThrow();
        break;
    case PalSpear::State::HITPAL:
        StateHitPal();
        break;
    case PalSpear::State::CATCHING:
        StateCatching();
        break;
    case PalSpear::State::SUCCESS:
        StateSuccess();
        break;
    case PalSpear::State::FAIL:
        StateFail();
        break;
    default:
        break;
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

void PalSpear::StateThrow()
{
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    transform->Pos() += direction * speed * DELTA;
    transform->Pos() += tmp * DELTA;
    speed -= DELTA * 3;
    if (speed <= 0.0f)
    {
        speed = 0.0f;
        if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
        {
            transform->Pos().y = terrain->GetHeight(transform->GlobalPos());
            time += DELTA; // �ð� ����� ���� ������ ����
            if (time > LIFE_SPAN)
            {
                transform->SetActive(false);
                speed = 15.0f;
                downForce = 0.0f;
            }
        }
    }
    if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
    {
        Vector3 normal;
        transform->Pos().y = terrain->GetHeight(transform->GlobalPos(), &normal);
        normal *= -1;
        Vector3 tmpDir = (direction + tmp) * -1;
        //tmpDir = tmpDir.GetNormalized();
        Vector3 tmpD = 2 * normal * (Dot(tmpDir, normal));
        tmpDir *= -1;
        direction = (tmpDir + tmpD).GetNormalized();
        downForce = 0.0f;
        speed *= 0.7;
    }
}

void PalSpear::StateHitPal()
{
    transform->Pos() += Vector3(0.0f, 1.0f, 0.0f) * 2 * DELTA;
    transform->Pos() += transform->Right() * 2 * DELTA;
    transform->Pos() += transform->Back() * 2 * DELTA;

}

void PalSpear::StateCatching()
{
}

void PalSpear::StateSuccess()
{
}

void PalSpear::StateFail()
{
}
