#include "Framework.h"

Penguin::Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform),instancing(instancing), index(index)
{

    // ±ê Çãºê Å×½ºÆ®
    name = "ÆëÅ°";
    modelName = "PenGuin";
    level = 1;
    speed = 5; //
    maxHP = 100;
    curHP = 100;
    isInvincible = false;

    // 
    skill[0] = new Tornado();
    skill[0]->Setpal(this); // 
    skill[0]->SetSkill();   // 

    // 
    IceSpear* tmp = new IceSpear();
    tmp->SetHeight(Vector3(0, 1.8f, 0)); //
    skill[1] = tmp;
    skill[1]->Setpal(this); // 
    skill[1]->SetSkill();   // 

    skill[2] = new IronSpike();
    skill[2]->Setpal(this); // 
    skill[2]->SetSkill();   // 

    // 
    icon = Texture::Add(L"Textures/Model/PenGuin/T_Penguin_icon_normal.png");
    iconC = Texture::Add(L"Textures/Model/PenGuin/T_Penguin_icon_normal_C.png");

    root = new Transform(); // 

    //
    collider = new CapsuleCollider(35, 20); // 
    collider->SetParent(root);
    collider->Rot().z = XMConvertToRadians(90.0f);
    collider->Pos() = { 10, 0, 0 };
    collider->SetActive(true); //

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //
    eventIters.resize(instancing->GetClipSize());

    //
    SetEvent((int)ACTION::ATTACK, bind(&Penguin::EndAttack, this), 1.5f);
    SetEvent((int)ACTION::DAMAGE, bind(&Penguin::EndDamage, this), 0.3f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // 
    }

    //
    tmpN = 0;

    velocity = { 0, 0, 0 };
    target = nullptr;

    

}

Penguin::~Penguin()
{
    // 
    delete collider;
    delete root;

    // 
    delete transform;
}

void Penguin::Update()
{
    //
    if (!transform->Active())
    {
        return;
    }
    
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
    //
    if (target == nullptr && !isSpawned)
    {
        MoveWithOutTarget();

        if ((PlayerManager::Get()->GetPlayer()->Pos() - transform->Pos()).Length() < 15.0f)
        {
            target = PlayerManager::Get()->GetPlayer();
        }
    }
    else if (target != nullptr && !target->Active() && !isSpawned)
    {
        target = nullptr;
        if ((PlayerManager::Get()->GetPlayer()->Pos() - transform->Pos()).Length() < 15.0f)
        {
            target = PlayerManager::Get()->GetPlayer();
        }
    }

    //if (target && !isSpawned)
    if (target && !isSpawned)
    {
        velocity = target->GlobalPos() - transform->GlobalPos(); // 
        Move(); //
    }

    if (target && isSpawned)
    {
        velocity = target->GlobalPos() - transform->GlobalPos(); //

        if (PlayerPalsManager::Get()->GetMode() == PlayerPalsManager::MODE::WORK)
        {
            MoveW();
        }
        else
        {
            Move(); //
        }
    }
    else if (target != nullptr && !target->Active() && isSpawned)
    {
        target = nullptr;
    }


    if (isSpawned && PlayerPalsManager::Get()->GetPathSize() != 0 && target == nullptr)
    {
        destVel = PlayerPalsManager::Get()->destPos - transform->GlobalPos();

        MoveP();
    }

    ExecuteEvent(); //
    UpdateUI(); //UI 

    if (!isSpawned && target)
    {
        emote->Pos() = transform->Pos() + CAM->Back() + CAM->Up() + CAM->Right()*0.5f;
        emote->Rot().y = CAM->GetParent()->Rot().y + XM_PI;
        emote->Update();
    }

    root->SetWorld(instancing->GetTransformByNode(index, 4));
    //root->SetWorld(instancing->GetTransformByNode(index, tmpN));
    collider->UpdateWorld(); //

    //if (KEY_DOWN('Q'))
    //{
    //    tmpN++;
    //}
    //else if (KEY_DOWN('E'))
    //{
    //    tmpN = 0;;
    //
    //}

    // 
    //if (KEY_DOWN('K') && !skill[0]->Active())
    //{
    //    Attack();
    //    //FieldAtack();
    //}

    for (int i = 0; i < 3; i++)
    {
        if (skill[i] !=nullptr)
        {
            skill[i]->Update();

        }
    }


    

}

void Penguin::Render()
{
    //
    if (!transform->Active()) return;
    collider->Render();

    if (!isSpawned && target)
    {
        blendState[1]->SetState();
        emote->Render();
        blendState[0]->SetState();
    }

    for (int i = 0; i < 3; i++)
    {
        if (skill[i] != nullptr)
        {
            skill[i]->Render();

        }
    }
}

void Penguin::ShadowRender()
{
    
}

void Penguin::PostRender()
{
    //
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
    //
    if (!transform->Active()) return;
    ///collider->GUIRender();
    //ImGui::Text("Node : %d", &tmpN);
    skill[1]->GUIRender();

    //ImGui::Text("% f", destVel.Length());
}

void Penguin::Attack()
{
    // ??? ????
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // ??? ?????
    //ransSkill = RANDOM->Int(1, 1);
    //skill[ransSkill]->SetActive(true);
    //skill[ransSkill]->SetEnemy(target);
    //skill[ransSkill]->SetSkill();
    //skill[ransSkill]->SkillSound(transform->GlobalPos());
    //MyPalSkillManager::Get()->AddFieldSkill(skill[ransSkill]);

    //ransSkill = RANDOM->Int(1, 1);
    skill[1]->SetActive(true);
    skill[1]->SetEnemy(target);
    skill[1]->SetSkill();
    skill[1]->SkillSound(transform->GlobalPos());
    MyPalSkillManager::Get()->AddFieldSkill(skill[1]);

}

void Penguin::FieldAttack()
{
    // ??? ????
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // ??? ?????
    //ransSkill = RANDOM->Int(1, 1);
    //skill[ransSkill]->SetActive(true);
    //skill[ransSkill]->SetSkill();
    //skill[ransSkill]->SetEnemy(target);
    //skill[ransSkill]->SkillSound(transform->GlobalPos());
    //FieldPalSkillManager::Get()->AddFieldSkill(skill[ransSkill]);
    //ransSkill = RANDOM->Int(1, 1);
    skill[1]->SetActive(true);
    skill[1]->SetSkill();
    skill[1]->SetEnemy(target);
    skill[1]->SkillSound(transform->GlobalPos());
    FieldPalSkillManager::Get()->AddFieldSkill(skill[1]);
}

void Penguin::Damage()
{
    // 
    //if (action == ACTION::DAMAGE) return; // 

    //
    //curHP -= 200 * DELTA;
    if (skillType == 0)
    {
        curHP -= damage * DELTA;
    }
    else if (skillType == 1)
    {
        curHP -= damage;
    }
    palHpBar->SetAmount(curHP / maxHP); // 

    // 
    if (curHP <= 0)
    {
        // 
        //SetAction(ACTION::DIE); 

        // 
        isDead = true;
        transform->SetActive(false);
        return;//
    }

    // 
    action = ACTION::DAMAGE;
    instancing->PlayClip(index, (int)ACTION::DAMAGE);
    eventIters[(int)ACTION::DAMAGE] = totalEvent[(int)ACTION::DAMAGE].begin();
}

void Penguin::Spawn(Vector3 pos)
{
    transform->SetActive(true); //
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // 
                             // 

    curHP = maxHP;
    //hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;
}

void Penguin::Summons(Vector3 pos)
{
    transform->SetActive(true); //
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
    if (totalEvent[clip].count(timeRatio) > 0) return; // 
    totalEvent[clip][timeRatio] = event;
}

void Penguin::ExecuteEvent()
{
    int index = (int)action; //
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //

    if (eventIters[index]->first > ratio) return; // 

    eventIters[index]->second(); //
    eventIters[index]++;
}

void Penguin::EndAttack()
{
    SetAction(ACTION::IDLE);
}

void Penguin::EndDamage()
{
    SetAction(ACTION::IDLE); //
}

void Penguin::SetAction(ACTION action)
{
    if (action == this->action) return;

    this->action = action; //
    instancing->PlayClip(index, (int)action); //
    eventIters[(int)action] = totalEvent[(int)action].begin();
}

void Penguin::Move()
{
    // ???????? ?????
    if (action == ACTION::ATTACK) return; // 
    if (action == ACTION::DAMAGE) return; // 
    if (action == ACTION::WORK) return; // 
    //if (action == ACTION::) return; // 

    if (velocity.Length() < 5)
    {
        if (isSpawned)
        {
            Attack();
        }
        else
        {
            FieldAttack();
        }
        //speed = 0;
        //SetAction(ACTION::IDLE);
    }
    else if (velocity.Length() < 15) // 
    {
        speed = 2;
        SetAction(ACTION::WALK);

    }
    else if (velocity.Length() < 50)
    {
        speed = 4; //
        SetAction(ACTION::RUN);
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
    // 

}

void Penguin::MoveP()
{
    // 
    if (action == ACTION::ATTACK) return; //
    if (action == ACTION::DAMAGE) return; // 
    if (action == ACTION::WORK) return; //
    //if (action == ACTION::) return; // 


    Vector3 temp = (CAM->GlobalPos() + CAM->Right() * 0.8f + CAM->Forward() * 6.5f);
    Vector3 real = { temp.x,LandScapeManager::Get()->GetTerrain()->GetHeight(temp),temp.z };


    float distance = (real - transform->Pos()).Length();

    if (distance < 0.5)
    {
        speed = 0;
        SetAction(ACTION::IDLE);
    }
    else if (distance >= 8.0f) // 
    {
        speed = 8; //
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

void Penguin::MoveW()
{
    if (action == ACTION::ATTACK) return; // 
    if (action == ACTION::DAMAGE) return; // 
    //if (action == ACTION::WORK) return; // 

    if (velocity.Length() < 5)
    {
        speed = 0;
        SetAction(ACTION::WORK);
        StructureManager::Get()->GetPalBox()->SetProgress(true);

        if (!StructureManager::Get()->isPalBoxWork())
        {
            target = nullptr;
            SetAction(ACTION::IDLE);
        }
    }
    else
    {
        speed = 4;
        SetAction(ACTION::RUN);
        StructureManager::Get()->GetPalBox()->SetProgress(false);
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
    else if (moveTime < r)
    {
        SetAction(ACTION::IDLE);
    }
    else
    {
        randomDir = { RANDOM->Float(-1.0,1.0f),0,RANDOM->Float(-1.0,1.0f) };
        r = RANDOM->Float(3.5f, 6.0f);
        moveTime = 0.0f;
    }

}

void Penguin::UpdateUI()
{
    //
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
    palQuad->UpdateWorld(); // 

    palHpBar->Pos() = palQuad->Pos() + Vector3(0.0, -10.0f, 0.0f);
    palHpBar->UpdateWorld(); // 

}

//void Penguin::ClipSync()
//{
//    if ((ACTION)frameBuffer->Get().cur.clip != action)
//    {
//        PlayClip((int)action);
//    }
//}


