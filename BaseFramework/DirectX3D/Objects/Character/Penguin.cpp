#include "Framework.h"

Penguin::Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    :transform(transform), instancing(instancing), index(index)
{
    root = new Transform(); // �ݶ��̴��� ��ġ�� ���(��ġ)

    //�浹ü
    collider = new CapsuleCollider(35, 20); // ������
    collider->SetParent(root);
    collider->Rot().z = XMConvertToRadians(90.0f);
    collider->Pos() = { 10, 0, 0 };
    collider->SetActive(true); //�浹ü ���̱� ���� ���� �� �κ� false

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //���� ���� ���� ���ڸ�ŭ �̺�Ʈ ������¡
    eventIters.resize(instancing->GetClipSize());

    //�̺�Ʈ ����
    SetEvent((int)ACTION::DAMAGE, bind(&Penguin::EndDamage, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // ��ϵǾ� ���� �̺�Ʈ�� ������������ �ݺ��� ����
    }

    //ĳ���� UI �߰�
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
    hpBar->SetActive(false);

    tmpN = 0;
}

Penguin::~Penguin()
{
    // ��ü ����
    delete collider;
    delete root;

    // �ӽ� ����
    delete transform;

    // ü�¹� ����
    delete hpBar;
}

void Penguin::Update()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    //ClipSync();
    velocity = target->GlobalPos() - transform->GlobalPos(); // �ӷ±��� : ǥ���� �ڽ��� �Ÿ�

    ExecuteEvent(); // �̺�Ʈ�� ������ �ϸ� �����ϱ�
    Move(); //�����̱�
    UpdateUI(); //UI ������Ʈ

    root->SetWorld(instancing->GetTransformByNode(index, 4));
    //root->SetWorld(instancing->GetTransformByNode(index, tmpN));
    collider->UpdateWorld(); //�浹ü ������Ʈ

    //if (KEY_DOWN('Q'))
    //{
    //    tmpN++;
    //}
    //else if (KEY_DOWN('E'))
    //{
    //    tmpN = 0;;
    //
    //}
}

void Penguin::Render()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    collider->Render();

}

void Penguin::PostRender()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    if (velocity.Length() >= 15.0f) return;
    hpBar->Render();

}

void Penguin::GUIRender()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    ///collider->GUIRender();
    //ImGui::Text("Node : %d", &tmpN);
}

void Penguin::Damage()
{
    //ü�¿� -
    curHP -= 20;
    hpBar->SetAmount(curHP / maxHP); // ü�� ������ ���� ü�¹� ����

    // ü���� ������ �ٴڳ���
    if (curHP <= 0)
    {
        // �״� ��� ������ ����
        //SetAction(ACTION::DIE); 
        
        // ����� �ٷ� ��Ȱ��ȭ
        transform->SetActive(false);
        return;//�� �Լ� ����
    }

    // ���� �� �׾����� �� �κ���� �´� ���� ����
    action = ACTION::DAMAGE;
    instancing->PlayClip(index, (int)ACTION::DAMAGE);
    eventIters[(int)ACTION::DAMAGE] = totalEvent[(int)ACTION::DAMAGE].begin();
}

void Penguin::Spawn(Vector3 pos)
{
    transform->SetActive(true); //��Ȱ��ȭ���ٸ� Ȱ��ȭ ����
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // ��ȯ ��� �ִٸ� ��ȯ��Ǻ���
                             // ���⼱ �ٷ� ���̵�

    curHP = maxHP;
    hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;
}

void Penguin::SetTarget(Transform* target)
{
    this->target = target;
}

void Penguin::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0) return; // ���� ����� �̺�Ʈ�� ������ ����
    totalEvent[clip][timeRatio] = event;
}

void Penguin::ExecuteEvent()
{
    int index = (int)action; //���� ���� �޾ƿ���
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //����� �ð� ������ ��ü ����ð�

    if (eventIters[index]->first > ratio) return; // ���� �ð��� ������ ���ؿ� �� ��ġ�� ����(�����)

    eventIters[index]->second(); //��ϵ� �̺�Ʈ ����
    eventIters[index]++;
}

void Penguin::EndDamage()
{
    SetAction(ACTION::IDLE); //�¾Ұ�, �� �׾���, ���������� �������
}

void Penguin::SetAction(ACTION action)
{
    if (action == this->action) return; 

    this->action = action; //�Ű������� ���� ���� ��ȭ
    instancing->PlayClip(index, (int)action); //�ν��Ͻ� �� �ڱ� Ʈ���������� ���� ���� ����
    eventIters[(int)action] = totalEvent[(int)action].begin();
}

void Penguin::Move()
{
    // �ȿ����̴� ���ǵ�
    if (action == ACTION::ATTACK) return; // ������ ���� �������� ����
    if (action == ACTION::DAMAGE) return; // ���� ���� �������� ����
    if (action == ACTION::WORK) return; // �۾��� ���� �������� ����
    //if (action == ACTION::) return; // �߰� ����

    if (velocity.Length() < 15) // ǥ���� �Ÿ��� ����� ����
    {
        speed = 4; //�� ��� ��������
        SetAction(ACTION::RUN);
    }
    else if (velocity.Length() < 30)
    {
        speed = 2;
        SetAction(ACTION::WALK);
    }
    else
    {
        speed = 0;
        SetAction(ACTION::IDLE);
    }
    velocity.y = 0.0f;
    transform->Pos() += velocity.GetNormalized() * speed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
    // �� ������(�� Back()�� ������ ��

}

void Penguin::UpdateUI()
{
    //(���� �ٲ�� �� ���ڵ� �ٲ� ��)
    barPos = transform->Pos() + Vector3(0, 1.8f, 0);

    if (!CAM->ContainPoint(barPos))
    {
        //hpBar->Scale() = {0, 0, 0};
        hpBar->SetActive(false);
        return;
    }

    if (!hpBar->Active()) hpBar->SetActive(true);

    // ����Ʈ�� ���� �Լ��� ȣ���Ͽ� 2D �̹����� ��ġ�� ����
    hpBar->Pos() = CAM->WorldToScreen(barPos); // ��� ��������(=3D��) ��ü�� ����Ʈ(=2D)�� ����
                                               // �̷� ����� ĵ�����̶�� �Ѵ�

    float scale = 100 / velocity.Length(); // �ӽ� ũ�� ������ �����ؼ�, ǥ���� Ʈ�������� �Ÿ��� ����
                                           // UI ũ�Ⱑ �ִ� 100�ȼ����� ���� ����

    scale = Clamp(0.1f, 1.0f, scale); // �ִ� �ּ� ������ �ٽ� �ش� (�ִ� ���� ���� ����)
                                      // ���� ����� ũ�⸦ �츮�� �ʹٸ� �� ��° �Ű������� �� ���� �ָ� �ȴ�


    // *���� ü�¹�, �ٸ� UI ������ ���� �ʿ�
    //hpBar->Scale() = { scale, scale, scale };
    hpBar->Scale() = { 0.3f, 0.3f, 0.3f };

    hpBar->UpdateWorld(); // ������ ���� ������Ʈ
}

//void Penguin::ClipSync()
//{
//    if ((ACTION)frameBuffer->Get().cur.clip != action)
//    {
//        PlayClip((int)action);
//    }
//}


