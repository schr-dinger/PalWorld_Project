#include "Framework.h"

Mammoth::Mammoth(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:transform(transform), instancing(instancing), index(index)
{
    name = "�׸���";
    modelName = "Mammoth";
    level = 30;
    speed = 5; //�ӷ� : �⺻ ����
    maxHP = 1000;
    curHP = 1000;

    // �θ𿡼� ������ ��ų ����
    skill[0] = new Tornado();
    skill[0]->Setpal(this); // ��ų ���� ��ġ �޾ư��� �Լ�, �� ���� ��ġ����
    skill[0]->SetSkill();   // ��ų ����(���� ��ġ), 

    // ��� ������ �߰�
    icon = Texture::Add(L"Textures/Model/Mammoth/T_GrassMammoth_icon_normal.png");
    iconC = Texture::Add(L"Textures/Model/Mammoth/T_GrassMammoth_icon_normal_C.png");

    root = new Transform(); // �ݶ��̴��� ��ġ�� ���(��ġ)

    //�浹ü
    collider = new CapsuleCollider(200, 200); // ������
    collider->SetParent(root);
    collider->Pos() = { 0, -20, -180 };
    collider->SetActive(true); //�浹ü ���̱� ���� ���� �� �κ� false

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //���� ���� ���� ���ڸ�ŭ �̺�Ʈ ������¡
    eventIters.resize(instancing->GetClipSize());

    //�̺�Ʈ ����
    SetEvent((int)ACTION::ATTACK, bind(&Mammoth::EndAttack, this), 1.5f);
    SetEvent((int)ACTION::DAMAGE, bind(&Mammoth::EndDamage, this), 0.9f);

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

    velocity = { 0, 0, 0 };
    target = nullptr;

}

Mammoth::~Mammoth()
{
    // ��ü ����
    delete collider;
    delete root;

    // �ӽ� ����
    delete transform;

    // ü�¹� ����
    delete hpBar;
}

void Mammoth::Update()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;

    Ray ray;
    ray.dir = CAM->Forward();
    ray.pos = CAM->GlobalPos();
    Contact contact;
    if (collider->IsRayCollision(ray, &contact))
    {
        isUIOn = true;
        onUITime = 0.0f;
    }
    if (isUIOn)
    {
        onUITime += DELTA;
    }
    if (onUITime > offUITime)
    {
        isUIOn = false;
    }

    //ClipSync();
    //������
    if (target == nullptr && !isSpawned)
    {
        MoveWithOutTarget();
    }

    if (target)
    {
        velocity = target->GlobalPos() - transform->GlobalPos(); // �ӷ±��� : ǥ���� �ڽ��� �Ÿ�
        Move(); //�����̱�
    }

    if (isSpawned && PlayerPalsManager::Get()->GetPathSize() != 0 && target == nullptr)
    {
        destVel = PlayerPalsManager::Get()->destPos - transform->GlobalPos();

        MoveP();
    }

    ExecuteEvent(); // �̺�Ʈ�� ������ �ϸ� �����ϱ�
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

    // ��ų �׽�Ʈ
    //if (KEY_DOWN('K') && !skill[0]->Active())
    //{
    //    Attack();
    //    //FieldAtack();
    //}
    skill[0]->Update();

}

void Mammoth::Render()
{
    if (!transform->Active()) return;
    collider->Render();
    skill[0]->Render();
}

void Mammoth::ShadowRender()
{
}

void Mammoth::PostRender()
{
    if (!transform->Active()) return;
    if ((PlayerManager::Get()->GetPlayer()->Pos() - transform->Pos()).Length() >= 15.0f) return;
    if (!isUIOn) return;
    hpBar->Render();

    if (hpBar->Active())
    {
        Vector3 tmp = transform->Pos() + Vector3(0, 2.0f, 0);
        //tmp = CAM->WorldToScreen(tmp);
        tmp = hpBar->GlobalPos();
        //tmp.x += 30.0f;
        tmp.y += 35.0f;

        string tmpString = name + " �׽�Ʈ��";
        Font::Get()->SetStyle("Default2");
        Font::Get()->RenderText(tmpString, { tmp.x, tmp.y }, 1);
        Font::Get()->SetStyle("Default");
        Font::Get()->GetDC()->EndDraw();
        Font::Get()->GetDC()->BeginDraw();

    }
}

void Mammoth::GUIRender()
{
    //if (!transform->Active()) return;
    //ImGui::Text("Time : %f", onUITime);
}

void Mammoth::Attack()
{
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // ��ų ��Ƽ��
    skill[0]->SetActive(true);
    skill[0]->SetSkill();
    MyPalSkillManager::Get()->AddFieldSkill(skill[0]);
}

void Mammoth::FieldAttack()
{
    // ��� ����
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // ��ų ��Ƽ��
    skill[0]->SetActive(true);
    skill[0]->SetSkill();
    FieldPalSkillManager::Get()->AddFieldSkill(skill[0]);

}

void Mammoth::Damage()
{
    // ������ �Ǵ� ���ǵ�
//if (action == ACTION::DAMAGE) return; // �°� ���� �� �� �´´�.

//ü�¿� -
    curHP -= 200 * DELTA;
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

void Mammoth::Spawn(Vector3 pos)
{
    transform->SetActive(true); //��Ȱ��ȭ���ٸ� Ȱ��ȭ ����
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // ��ȯ ��� �ִٸ� ��ȯ��Ǻ���
                             // ���⼱ �ٷ� ���̵�

    curHP = maxHP;
    //hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;

}

void Mammoth::Summons(Vector3 pos)
{
    transform->SetActive(true); //��Ȱ��ȭ���ٸ� Ȱ��ȭ ����
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // 
    //hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;

}

void Mammoth::SetTarget(Transform* target)
{
    this->target = target;
}

void Mammoth::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0) return; // ���� ����� �̺�Ʈ�� ������ ����
    totalEvent[clip][timeRatio] = event;

}

void Mammoth::ExecuteEvent()
{
    int index = (int)action; //���� ���� �޾ƿ���
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //����� �ð� ������ ��ü ����ð�

    if (eventIters[index]->first > ratio) return; // ���� �ð��� ������ ���ؿ� �� ��ġ�� ����(�����)

    eventIters[index]->second(); //��ϵ� �̺�Ʈ ����
    eventIters[index]++;

}

void Mammoth::EndAttack()
{
    SetAction(ACTION::IDLE);

}

void Mammoth::EndDamage()
{
    SetAction(ACTION::IDLE); //�¾Ұ�, �� �׾���, ���������� �������
}

void Mammoth::SetAction(ACTION action)
{
    if (action == this->action) return;

    this->action = action; //�Ű������� ���� ���� ��ȭ
    instancing->PlayClip(index, (int)action); //�ν��Ͻ� �� �ڱ� Ʈ���������� ���� ���� ����
    eventIters[(int)action] = totalEvent[(int)action].begin();

}

void Mammoth::Move()
{
    // �ȿ����̴� ���ǵ�
    if (action == ACTION::ATTACK) return; // ������ ���� �������� ����
    if (action == ACTION::DAMAGE) return; // ���� ���� �������� ����
    //if (action == ACTION::WORK) return; // �۾��� ���� �������� ����
    //if (action == ACTION::) return; // �߰� ����

    if (velocity.Length() < 5)
    {
        speed = 0;
        SetAction(ACTION::IDLE);
    }
    else if (velocity.Length() < 50) // ǥ���� �Ÿ��� ����� ����
    {
        speed = 4; //�� ��� ��������
        SetAction(ACTION::RUN);
    }
    else if (velocity.Length() < 100)
    {
        speed = 2;
        SetAction(ACTION::WALK);
    }
    else
    {
        //speed = 0;
        target = nullptr;
        SetAction(ACTION::IDLE);
    }

    velocity.y = 0.0f;
    transform->Pos() += velocity.GetNormalized() * speed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
    // �� ������(�� Back()�� ������ ��
}

void Mammoth::MoveP()
{
    // �ȿ����̴� ���ǵ�
    if (action == ACTION::ATTACK) return; // ������ ���� �������� ����
    if (action == ACTION::DAMAGE) return; // ���� ���� �������� ����
    //if (action == ACTION::WORK) return; // �۾��� ���� �������� ����
    //if (action == ACTION::) return; // �߰� ����


    Vector3 temp = (CAM->GlobalPos() + CAM->Right() * 0.8f + CAM->Forward() * 6.5f);
    Vector3 real = { temp.x,LandScapeManager::Get()->GetTerrain()->GetHeight(temp),temp.z };


    float distance = (real - transform->Pos()).Length();

    if (distance < 0.5)
    {
        speed = 0;
        SetAction(ACTION::IDLE);
    }
    else if (distance >= 8.0f) // ǥ���� �Ÿ��� ����� ����
    {
        speed = 8; //�� ��� ��������
        SetAction(ACTION::RUN);
    }
    else if (distance < 8.0f)
    {
        speed = 4;
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

}

void Mammoth::MoveWithOutTarget()
{
    moveTime += DELTA;

    if (moveTime < 3.0f)
    {
        SetAction(ACTION::WALK);
        transform->Pos() += randomDir.GetNormalized() * 1.5f * DELTA;
        transform->Rot().y = atan2(randomDir.x, randomDir.z) + XM_PI;
    }
    else if (moveTime < 5.0f)
    {
        SetAction(ACTION::IDLE);
    }
    else
    {
        randomDir = { RANDOM->Float(-1.0,1.0f),0,RANDOM->Float(-1.0,1.0f) };
        moveTime = 0.0f;
    }
}

void Mammoth::UpdateUI()
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

