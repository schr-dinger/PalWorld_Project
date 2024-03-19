#include "Framework.h"

Penguin::Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform),instancing(instancing), index(index)
{
    name = "��Ű";
    modelName = "PenGuin";
    level = 1;
    speed = 5; //�ӷ� : �⺻ ����
    maxHP = 100;
    curHP = 100;
    isInvincible = false;

    // �θ𿡼� ������ ��ų ����
    skill[0] = new Tornado();
    skill[0]->Setpal(this); // ��ų ���� ��ġ �޾ư��� �Լ�, �� ���� ��ġ����
    skill[0]->SetSkill();   // ��ų ����(���� ��ġ), 

    // ��� ������ �߰�
    icon = Texture::Add(L"Textures/Model/PenGuin/T_Penguin_icon_normal.png");
    iconC = Texture::Add(L"Textures/Model/PenGuin/T_Penguin_icon_normal_C.png");

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
    SetEvent((int)ACTION::ATTACK, bind(&Penguin::EndAttack, this), 1.5f);
    SetEvent((int)ACTION::DAMAGE, bind(&Penguin::EndDamage, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // ��ϵǾ� ���� �̺�Ʈ�� ������������ �ݺ��� ����
    }

    //ĳ���� UI �߰�
    tmpN = 0;

    velocity = { 0, 0, 0 };
    target = nullptr;

    

}

Penguin::~Penguin()
{
    // ��ü ����
    delete collider;
    delete root;

    // �ӽ� ����
    delete transform;
}

void Penguin::Update()
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

    //if (target && !isSpawned)
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

void Penguin::Render()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    collider->Render();
    skill[0]->Render();

}

void Penguin::ShadowRender()
{
    
}

void Penguin::PostRender()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    if ((PlayerManager::Get()->GetPlayer()->Pos() - transform->Pos()).Length() >= 15.0f) return;
    if (!isUIOn) return;

    palQuad->Render();
    palHpBar->Render();

   
    if (palQuad->Active() && palHpBar->Active())
    {
        palQuad->UpdateWorld();

        string tmpString = to_string(level);
        //tmpString = "99";
        Font::Get()->SetStyle("FieldLvNum");
        Vector3 tmpFP = palQuad->Pos() + Vector3(-38.0f, 13.0f, 0.0f);
        Font::Get()->RenderText(tmpString, { tmpFP.x, tmpFP.y });

        tmpString = "LV";
        Font::Get()->SetStyle("FieldLv");
        tmpFP = palQuad->Pos() + Vector3(-50.0f, 7.0f, 0.0f);
        Font::Get()->RenderText(tmpString, { tmpFP.x, tmpFP.y });

        tmpString = name;
        Font::Get()->SetStyle("FieldName");
        tmpFP = palQuad->Pos() + Vector3(-11.0f, 11.0f, 0.0f);
        Font::Get()->RenderText(tmpString, { tmpFP.x, tmpFP.y });
        Font::Get()->SetStyle("Default");
        Font::Get()->GetDC()->EndDraw();
        Font::Get()->GetDC()->BeginDraw();
    }
}

void Penguin::GUIRender()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;
    ///collider->GUIRender();
    //ImGui::Text("Node : %d", &tmpN);
    //skill[0]->GUIRender();

    //ImGui::Text("% f", destVel.Length());
}

void Penguin::Attack()
{
    // ��� ����
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // ��ų ��Ƽ��
    skill[0]->SetActive(true);
    skill[0]->SetSkill();
    MyPalSkillManager::Get()->AddFieldSkill(skill[0]);

}

void Penguin::FieldAttack()
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

void Penguin::Damage()
{
    // ������ �Ǵ� ���ǵ�
    //if (action == ACTION::DAMAGE) return; // �°� ���� �� �� �´´�.

    //ü�¿� -
    curHP -= 200 * DELTA;
    palHpBar->SetAmount(curHP / maxHP); // ü�� ������ ���� ü�¹� ����

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
    //hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;
}

void Penguin::Summons(Vector3 pos)
{
    transform->SetActive(true); //��Ȱ��ȭ���ٸ� Ȱ��ȭ ����
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // 
    //hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;

}

void Penguin::SetTarget(Transform* target)
{
    this->target = target;
}

//void Penguin::Path(Vector3 start, Vector3 dest)
//{
//    //Ray ray;
//    //ray.pos = start;
//    //ray.dir = dest - start;
//    //Contact contact;
//    //for (Collider* collider : LandScapeManager::Get()->GetObstacles())
//    //{
//    //    //if (collider->IsRayCollision(ray) && Distance(collider->GlobalPos(),transform->GlobalPos()) < collider->GlobalScale().x + 20.0f )
//    //    //{
//    //    //    Path()
//    //    //}
//    //    //else
//    //    //{
//    //    //    break;
//    //    //}
//
//    //    if (collider->IsRayCollision(ray,&contact))
//    //    {
//    //        Vector3 temp = contact.hitPoint - ray.dir * (collider->GlobalScale().x);
//    //    }
//    //}
//
//}

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

void Penguin::EndAttack()
{
    SetAction(ACTION::IDLE);
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

void Penguin::MoveP()
{
    // �ȿ����̴� ���ǵ�
    if (action == ACTION::ATTACK) return; // ������ ���� �������� ����
    if (action == ACTION::DAMAGE) return; // ���� ���� �������� ����
    if (action == ACTION::WORK) return; // �۾��� ���� �������� ����
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

void Penguin::MoveWithOutTarget()
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

void Penguin::UpdateUI()
{
    //(���� �ٲ�� �� ���ڵ� �ٲ� ��)
    barPos = transform->Pos() + Vector3(0, 1.5f, 0);

    if (!CAM->ContainPoint(barPos))
    {
        palQuad->SetActive(false);
        palHpBar->SetActive(false);
        return;
    }

    if (!palQuad->Active()) palQuad->SetActive(true);
    if (!palHpBar->Active()) palHpBar->SetActive(true);

    palQuad->Pos() = CAM->WorldToScreen(barPos);
    palQuad->UpdateWorld(); // ������ ���� ������Ʈ

    palHpBar->Pos() = palQuad->Pos() + Vector3(0.0, -10.0f, 0.0f);
    palHpBar->UpdateWorld(); // ������ ���� ������Ʈ

}

//void Penguin::ClipSync()
//{
//    if ((ACTION)frameBuffer->Get().cur.clip != action)
//    {
//        PlayClip((int)action);
//    }
//}


