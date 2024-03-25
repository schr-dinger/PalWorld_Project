#include "Framework.h"

PlayerPalsManager::PlayerPalsManager()
{
    terrain = nullptr;
    //target = nullptr;

    selPal = 0;
    isSummonedSelPal = -1;
    pals.resize(100);

    palStateIcon = new Quad(stateIconSize);
    palStateIcon->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");

    InsertAllMAI(); // ��� �� �� �ν��Ͻ� ����(���� "��Ű" �ϳ�,)
    FOR(1)
    {
        Transform* transform = palsMAI["��Ű"]->Add();
        //transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Penguin(transform, palsMAI["��Ű"], palsMAIIndex["��Ű"]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
        palsMAIIndex["��Ű"]++;// �ش� �� �ν��Ͻ� �ε��� ����
        //pals.push_back(pal);
        pals[i] = pal;
        
    }
    
    //FOR(2)
    //{
    //    Transform* transform = palsMAI["�׸���"]->Add();
    //    //transform->SetActive(false);
    //    transform->Scale() *= 0.01;// ������ ������ ���⼭
    //    Pal* pal = new Mammoth(transform, palsMAI["�׸���"], palsMAIIndex["�׸���"]);
    //    // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
    //    //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
    //    palsMAIIndex["�׸���"]++;// �ش� �� �ν��Ͻ� �ε��� ����
    //    //pals.push_back(pal);
    //    pals[i+2] = pal;
    //
    //}

    FOR(1)
    {
        Transform* transform = palsMAI["��ũ����"]->Add();
        //transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new DarkWolf(transform, palsMAI["��ũ����"], palsMAIIndex["��ũ����"]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
        palsMAIIndex["��ũ����"]++;// �ش� �� �ν��Ͻ� �ε��� ����
        //pals.push_back(pal);
        pals[i + 1] = pal;

    }


    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);

    // �ӵ� �̸� �� �� ������Ʈ�ϰ� ��Ȱ��ȭ
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        iter->second->Update();
        for (Transform* palTransform : iter->second->GetInstancingTransform())
        {
            palTransform->SetActive(false);
        }
        //iter->second->Render();
    }
    for (Pal* pal : pals)
    {
        if (pal != nullptr)
        {
            pal->Update();
            //pal->Render();
            //pal->GetTransform()->SetActive(false);
        }
    }

    // �浹��
    lastPos = {};
}

PlayerPalsManager::~PlayerPalsManager()
{
    // �� �ν��Ͻ� ����
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        delete iter->second;
    }

    for (Pal* pal : pals)
        delete pal;

    FOR(2)  delete blendState[i];

    delete palStateIcon;
}

void PlayerPalsManager::Update()
{
    OnGround(terrain);
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        iter->second->Update();
    }
    // �浹 ���� ����
    Collision();

    if (selPal != -1)
    {
        if (pals[selPal] == nullptr)
        {
            return;
        }
        if (!pals[selPal]->GetTransform()->Active()) return;
        lastPos = pals[selPal]->GetTransform()->GlobalPos();

        SetTarget();
        if (!pals[selPal]->target || !pals[selPal]->target->Active())
        {
            PathFinding();
            Move();
        }
        //palsMAI[pals[selPal]->name]->Update();
        //pals[selPal]->Update();
        //if (KEY_DOWN('L') && !pals[selPal]->skill[0]->Active())
        //{
        //    Vector3 tmpDIr = pals[selPal]->GetTransform()->Pos() - PlayerManager::Get()->GetPlayer()->Pos();
        //    tmpDIr.y = 0;
        //    tmpDIr = tmpDIr.GetNormalized();
        //    pals[selPal]->GetTransform()->Rot().y = atan2(tmpDIr.x, tmpDIr.z);
        //    pals[selPal]->GetTransform()->UpdateWorld();
        //    pals[selPal]->Attack();
        //}
        // ��ȯ�� �縸 ������Ʈ, �� �� �ν��Ͻ��� �̸� ��� ������Ʈ
        
        //palsMAI[pals[selPal]->name]->Update();
        lastPos = pals[selPal]->GetTransform()->GlobalPos();

        pals[selPal]->Update();
        
        palStateIcon->Pos() = pals[selPal]->GetTransform()->Pos() + Vector3(0.0f, 2.0f, 0.0f);
        palStateIcon->Rot().y = CAM->GetParent()->Rot().y + XM_PI;
    }
    
    palStateIcon->Update();

    //if (selPal != -1 && pals[selPal] != nullptr && pals[selPal]->GetTransform()->Active())
    //{
    //    lastPos = pals[selPal]->GetTransform()->GlobalPos();
    //}
}

void PlayerPalsManager::Render()
{
    // �׽�Ʈ : ��� Ȱ��ȭ
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        blendState[1]->SetState(); // ���� ����

        iter->second->Render();
        blendState[0]->SetState();

    }
    //for (Pal* pal : pals)
    //{
    //
    //    if (pal == nullptr)
    //    {
    //        continue;
    //    }
    //    pal->Render();
    //}

    //blendState[1]->SetState();
    //palStateIcon->Render();
    //blendState[0]->SetState();

    // ��ȯ�� �ȸ� Ȱ��ȭ, ��� ����(����� �� ������ ��ȯ)

    if (selPal != -1)
    {
        if (pals[selPal] == nullptr)
        {
            return;
        }
        blendState[1]->SetState(); // ���� ����
        palsMAI[pals[selPal]->name]->Render();
        if (pals[selPal]->GetTransform()->Active())
        {
            palStateIcon->Render();
        }
        blendState[0]->SetState();
    
        pals[selPal]->Render();
    }
}

void PlayerPalsManager::PostRender()
{
    if (selPal != -1)
    {
        if (pals[selPal] == nullptr)
        {
            return;
        }
        pals[selPal]->PostRender();
    }
    //for (Pal* pal : pals)
    //{
    //    if (pal != nullptr)
    //    {
    //        pal->PostRender();
    //    }
    //}
}

void PlayerPalsManager::ShadowRender()
{
    //for (Pal* pal : pals)
    //{
    //    if (pal != nullptr)
    //    {
    //        pal->ShadowRender();
    //    }
    //}
    //if (selPal != -1)
    //{
    //    if (!pals[selPal]->GetTransform()->Active())
    //    {
    //        return;
    //    }
    //    pals[selPal]->ShadowRender();
    //}
}

void PlayerPalsManager::GUIRender()
{
    if (pals[selPal] == nullptr)
    {
        return;
    }
    //ImGui::Text("MyPalsSIze : %d", pals.size());
    //ImGui::Text("pathsize : %d", path.size());
    //
    //ImGui::Text("destPosX : %f", destPos.x);
    //ImGui::Text("destPosY : %f", destPos.y);
    //ImGui::Text("destPosZ : %f", destPos.z);

    //if (selPal != -1)
    //{
    //    ImGui::Text("Mode : %d", mode);
    //
    //    //ImGui::Text("Target : %d", pals[selPal]->);
    //
    //}
    //
    //if (path.size() > 0)
    //{
    //    ImGui::Text("X: %f", path.back().x);
    //    ImGui::Text("y: %f", path.back().y);
    //    ImGui::Text("z: %f", path.back().z);
    //    ImGui::Text("X: %f", destPos.x);
    //    ImGui::Text("y: %f", destPos.y);
    //    ImGui::Text("z: %f", destPos.z);
    //}
    //pals[0]->GUIRender();

}

void PlayerPalsManager::SetTarget()
{
    //this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    // �Ƹ� �ʿ� ���� ��

    if (selPal != -1)
    {
        switch (mode)
        {
        case PlayerPalsManager::MODE::PASSIVE:
            pals[selPal]->SetTarget(nullptr);
            palStateIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_monitoring_button_0_2.png");

            break;
        case PlayerPalsManager::MODE::AGGRESSIVE:
            smallest = 100.0f;
            closePal = nullptr;

            for (Pal* pal : PalsManager::Get()->GetPalsVector())
            {
                if (pal->isDead)
                {
                    //smallest = 100.0f;
                    //closePal = nullptr;
                    continue;
                }

                float distance = (pals[selPal]->GetTransform()->Pos() - pal->GetTransform()->Pos()).Length();
                if (distance < smallest)
                {
                    smallest = distance;
                    closePal = pal;
                }
            }

            if (!closePal)
            {
                pals[selPal]->SetTarget(nullptr);
                mode = MODE::PASSIVE;
            }
            else
            {
                pals[selPal]->SetTarget(closePal->GetTransform());
            }

            palStateIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_pal_battle.png");
            break;

        case PlayerPalsManager::MODE::WORK:

            if (StructureManager::Get()->isPalBoxWork())
            {
                pals[selPal]->SetTarget(StructureManager::Get()->GetPalBox()->GetBuilding());
            }
            else
            {
                mode = MODE::PASSIVE;
            }

            palStateIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_pal_work.png");
            break;

       }
        // ���� ��Ÿ���ϴ� ���� �߰��ϱ�
        //if () // �Ÿ������(����), ���ݴ������� ��
        //pals[selPal]->SetTarget(target);
    }



}

void PlayerPalsManager::SetPlayer(Player* player)
{
    this->player = player;
}

bool PlayerPalsManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    Contact contact;
    float minDistance = FLT_MAX;
    if (selPal != -1)
    {
        if (pals[selPal] == nullptr)
        {
            return false;
        }
        if (pals[selPal]->GetCollider()->IsRayCollision(ray, &contact))
        {
            minDistance = contact.distance;
            hitPoint = contact.hitPoint;
        }
        
    }
    return minDistance != FLT_MAX; // �浹 Ȯ�� ������ ����
    return false; // �Ÿ� ���� �ȵǸ� �浹 ����
}

void PlayerPalsManager::OnGround(Terrain* terrain)
{
    
    //if (selPal != -1)
    //{
    //    pals[selPal]->GetTransform()->Pos().y = terrain->GetHeight(pals[selPal]->GetTransform()->GlobalPos());
    //}
    for (Pal* pal : pals)
    {
        if (pal != nullptr)
        {
            //pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
            pal->GetTransform()->Pos().y = Lerp(pal->GetTransform()->Pos().y, terrain->GetHeight(pal->GetTransform()->GlobalPos()), 10 * DELTA);

        }
    }
}

void PlayerPalsManager::InsertAllMAI()
{
    {
        // ��Ű �� �ν��Ͻ� �ֱ�
        ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("PenGuin");
        pal->ReadClip("Idle");
        pal->ReadClip("Walk");
        pal->ReadClip("Run");
        pal->ReadClip("Attack");
        pal->ReadClip("Damage");
        pal->ReadClip("Work");
        pal->SetTag("Penguin");
        palsMAI.insert({ "��Ű", pal });                                     // �ִ� �� 1.
        //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("��Ű", pal)); // �ִ� �� 2.
        palsMAIIndex.insert({ "��Ű", 0 }); // �� �ν��Ͻ� �ε����� map���� �߰�
                                            // "��Ű"��� key(�� �ν��Ͻ�)�� ���� �ε��� ��(0������),
                                            // ���� ���� ���� ������ �ε��� �� ����(���� ���̶� �ε����� �޶� �ٸ� ��ü)
    }
    // �� �߰��� �߰� �۾� �� �� ----------------------

    {
        ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("Mammoth");
        pal->ReadClip("Idle");
        pal->ReadClip("Walk");
        pal->ReadClip("Run");
        pal->ReadClip("Attack");
        pal->ReadClip("Damage");
        pal->SetTag("mammoth");
        palsMAI.insert({ "�׸���", pal });                                     // �ִ� �� 1.
        //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("��Ű", pal)); // �ִ� �� 2.
        palsMAIIndex.insert({ "�׸���", 0 }); // �� �ν��Ͻ� �ε����� map���� �߰�
                                            // "��Ű"��� key(�� �ν��Ͻ�)�� ���� �ε��� ��(0������),
                                            // ���� ���� ���� ������ �ε��� �� ����(���� ���̶� �ε����� �޶� �ٸ� ��ü)
    }

    {
        ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("DarkWolf");
        pal->ReadClip("Idle");
        pal->ReadClip("Walk");
        pal->ReadClip("Run");
        pal->ReadClip("Attack");
        pal->ReadClip("Damage");
        pal->SetTag("wolf");
        palsMAI.insert({ "��ũ����", pal });                                     // �ִ� �� 1.
        //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("��Ű", pal)); // �ִ� �� 2.
        palsMAIIndex.insert({ "��ũ����", 0 }); // �� �ν��Ͻ� �ε����� map���� �߰�
                                            // "��Ű"��� key(�� �ν��Ͻ�)�� ���� �ε��� ��(0������),
                                            // ���� ���� ���� ������ �ε��� �� ����(���� ���̶� �ε����� �޶� �ٸ� ��ü)
    }

}

void PlayerPalsManager::Collision()
{
    //if (selPal != -1)
    //{
    //    // ���ǿ����� ������ ȣ��
    //    if (FieldPalSkillManager::Get()->IsCollision(pals[selPal]->GetCollider())) // �ʵ� ��ų�� �¾��� ��
    //    {
    //        pals[selPal]->Damage();
    //    }
    //}

    if (selPal == -1) return;
    if (pals[selPal] == nullptr)
    {
        return;
    }
    if (!pals[selPal]->GetTransform()->Active()) return;
    // ��ȯ�� �Ѹ����� �����ϱ�

    for (Collider* obs : LandScapeManager::Get()->GetObstacles())
    {
        if (pals[selPal]->GetCollider()->IsCollision(obs) && obs->Active())
        {
            Vector3 nol = pals[selPal]->GetTransform()->GlobalPos() - obs->GlobalPos();
            nol.y = 0;
            nol = nol.GetNormalized();
            Vector3 dir = pals[selPal]->GetTransform()->GlobalPos() - lastPos;
            dir.y = 0;
            Vector3 tmpV1 = dir;
            Vector3 tmpV2 = obs->GlobalPos() - pals[selPal]->GetTransform()->GlobalPos();
            tmpV2.y = 0;
            if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
            Vector3 mDir = dir * -1;
            Vector3 tmp = nol * Dot(mDir, nol);
            Vector3 fDir = dir + tmp;
            pals[selPal]->GetTransform()->Pos() = lastPos + fDir;
            pals[selPal]->GetTransform()->UpdateWorld();
            //isCollision = true;
        }
    }


    if (FieldPalSkillManager::Get()->GetFieldSkills().size() == 0) return;
    for (int i = 0; i < FieldPalSkillManager::Get()->GetFieldSkills().size(); i++)
    {
        if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->IsCollision(pals[selPal]->GetCollider()))
            // ��ų�� �Ű����� 'collider'�� �浹�ߴٸ�
        {
            if (!FieldPalSkillManager::Get()->GetFieldSkills()[i]->Active())
            {
                continue;
            }
            if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "����â")
            {
                FieldPalSkillManager::Get()->GetFieldSkills()[i]->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
                pals[selPal]->skillType = 1;
            }
            else if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "������ũ")
            {
                FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->SetActive(false);
                pals[selPal]->skillType = 1;
            }
            else
            {
                pals[selPal]->skillType = 0;
            }
            FieldPalSkillManager::Get()->GetFieldSkills()[i]->SkillHitSound(pals[selPal]->GetTransform()->GlobalPos());
            //skill->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
            pals[selPal]->damage = FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetDamage();
            pals[selPal]->Damage();
            return;
        }
    }


    // �Ѹ����� ��ȯ�� �Ÿ� �Ʒ� �ʿ���� 240324
    //for (Pal* pal : pals)
    //{
    //    if (pal != nullptr)
    //    {
    //        // ���ǿ����� ������ ȣ��
    //        //if (FieldPalSkillManager::Get()->IsCollision(pal->GetCollider())) // �ʵ� ��ų�� �¾��� ��
    //        //{
    //        //    pal->Damage();
    //        //}
    //        if (FieldPalSkillManager::Get()->GetFieldSkills().size() == 0) continue;
    //        for (int i = 0; i < FieldPalSkillManager::Get()->GetFieldSkills().size(); i++)
    //        {
    //            if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->IsCollision(pal->GetCollider()))
    //                // ��ų�� �Ű����� 'collider'�� �浹�ߴٸ�
    //            {
    //                if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "����â")
    //                {
    //                    FieldPalSkillManager::Get()->GetFieldSkills()[i]->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
    //                    pal->skillType = 1;
    //                }
    //                if (FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetName() == "������ũ")
    //                {
    //                    FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetCol()->SetActive(false);
    //                    pal->skillType = 0;
    //                }
    //                else
    //                {
    //                    pal->skillType = 0;
    //                }
    //                FieldPalSkillManager::Get()->GetFieldSkills()[i]->SkillHitSound(pal->GetTransform()->GlobalPos());
    //                //skill->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
    //                pal->damage = FieldPalSkillManager::Get()->GetFieldSkills()[i]->GetDamage();
    //                pal->Damage();
    //                return;
    //            }
    //        }
    //    }
    //}

}

void PlayerPalsManager::PathFinding()
{
    if (pals[selPal] == nullptr) return;
    //if (pals[selPal]->target == nullptr) return;
    destPos = CAM->GlobalPos() + CAM->Right() * 0.8f + CAM->Forward() * 6.5f;

    if (Distance(pals[selPal]->GetTransform()->GlobalPos(), destPos) > 10.0f)
    {
        pathTime += DELTA;
    }
    else
    {
        pathTime = 0.0f;
    }


    if (pathTime > 1.0f)
    {
        //if (AStarManager::Get()->GetAStar()->IsCollisionObstacle(pals[selPal]->GetTransform()->GlobalPos(), destPos))
        //{
        //    SetPath();
        //}
        //else
        //{
        //    path.clear();
        //    path.push_back(destPos);
        //}

        SetPath();

        pathTime = 0.0f;
    }
}

//void PlayerPalsManager::SetPath()
//{
//    int startIndex = AStarManager::Get()->GetAStar()->FindCloseNode(pals[selPal]->GetTransform()->GlobalPos());
//    int endIndex = AStarManager::Get()->GetAStar()->FindCloseNode(destPos);
//
//    AStarManager::Get()->GetAStar()->GetPath(startIndex, endIndex, path); // ���� �� ���� path ���Ϳ� ����
//}

void PlayerPalsManager::SetPath()
{
    int startIndex = AStarManager::Get()->GetAStar()->FindCloseNode(pals[selPal]->GetTransform()->GlobalPos());
    int endIndex = AStarManager::Get()->GetAStar()->FindCloseNode(destPos);

    AStarManager::Get()->GetAStar()->GetPath(startIndex, endIndex, path); // ���� �� ���� path ���Ϳ� ����

    UINT pathSize = path.size(); // ó�� ���� ��� ���� ũ�⸦ ����

    while (path.size() > 2) // "������" ��� ��尡 1���� ���ϰ� �� ������
    {
        vector<Vector3> tempPath = path; // ���� �ӽ� ��� �޾ƿ���
        tempPath.erase(tempPath.begin()); // ���� ������ ����� (��ֹ��� �־��� ������ ������ �߰��� ���� ��)
        tempPath.pop_back(); // ���� ��ġ�� �������� �����ϱ� (�̹� �������� �����ϱ�)

        // ������ ������ ���� ����� ���ο� ���۰� ���� ����
        Vector3 start = path.back();
        Vector3 end = path.front();

        //�ٽ� ���� ��ο��� ��ֹ� ����� �� ���
        AStarManager::Get()->GetAStar()->MakeDirectionPath(start, end, tempPath);

        //��� ��� �ǵ��
        path.clear();
        path = tempPath;

        //��� ���Ϳ� ���ο� ���۰� ���� ����
        path.insert(path.begin(), end);
        path.push_back(start);

        // ����� �ٽ� �ߴµ� ���� ũ�Ⱑ �״�ζ�� = ���� �ٲ��� �ʾҴ�
        if (pathSize == path.size()) break; // �� �̻� ����� ����� ������ ����
        else pathSize = path.size(); // �پ�� ��� ����� �ݿ��� ���ְ� �ݺ����� �ٽ� ����
    }

    // �ٽ� ������, ���� �� �� �ִ� ��ο�, ���� �������� �ٽ� �ѹ� �߰��Ѵ�
    path.insert(path.begin(), destPos);

}

void PlayerPalsManager::Move()
{
    if (path.empty())
    {
        //SetState(IDLE);
        return;
    }

    //pals[selPal]->SetAction(Pal::ACTION::RUN);

    Vector3 dest = path.back();

    Vector3 direction = dest - pals[selPal]->GetTransform()->GlobalPos();

    direction.y = 0;
                    

    if (direction.Length() < 0.1f)
    {
        path.pop_back();
    }

    //velocity = direction.GetNormalized();
    //pals[selPal]->velocity = direction.GetNormalized();
    pals[selPal]->velocity = direction;

    //pals[selPal]->GetTransform()->Pos() += velocity * moveSpeed * DELTA;

    //pals[selPal]->GetTransform()->Pos() += pals[selPal]->velocity.GetNormalized() * 4.0f * DELTA;
    //pals[selPal]->GetTransform()->Rot().y = atan2(pals[selPal]->velocity.x, pals[selPal]->velocity.z) + XM_PI;


}

void PlayerPalsManager::Summons(Vector3 summonPos)
{
    if (selPal == -1) return;
    if (pals[selPal] == nullptr)
    {
        return;
    }
    pals[selPal]->isSpawned = true;
    pals[selPal]->Summons(summonPos); 
    isSummonedSelPal = selPal;
}

void PlayerPalsManager::SUmmonedPalActiveFalse()
{
    if (isSummonedSelPal == -1)
    {
        return; // ó�� ��ȯ��
    }
    if (pals[isSummonedSelPal] == nullptr)
    {
        return;
    }
    pals[isSummonedSelPal]->GetTransform()->SetActive(false);
    pals[isSummonedSelPal]->isSpawned = false;
}

void PlayerPalsManager::Caught(Pal* CaughtPal)
{
    // ���͸� ���� �����ؾ� ��, ����� ���� ���ϰ� ���� �����
    if (CaughtPal->name == "��Ű")
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* Cpal = new Penguin(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����

        palsMAIIndex[CaughtPal->name]++;// �ش� �� �ν��Ͻ� �ε��� ����
        for (int i = 0; i < pals.size(); i++)
        {
            if (pals[i] == nullptr)
            {
                pals[i] = Cpal;
                return;
            }
        }
        //pals.push_back(Cpal);
    }
    else if (CaughtPal->name == "�׸���") // ���� �ٸ� ���� �ִٸ� ���⼭
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* Cpal = new Mammoth(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);

        palsMAIIndex[CaughtPal->name]++;// �ش� �� �ν��Ͻ� �ε��� ����
        for (int i = 0; i < pals.size(); i++)
        {
            if (pals[i] == nullptr)
            {
                pals[i] = Cpal;
                return;
            }
        }
    }
    else if (CaughtPal->name == "��ũ����") // ���� �ٸ� ���� �ִٸ� ���⼭
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* Cpal = new DarkWolf(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);

        palsMAIIndex[CaughtPal->name]++;// �ش� �� �ν��Ͻ� �ε��� ����
        for (int i = 0; i < pals.size(); i++)
        {
            if (pals[i] == nullptr)
            {
                pals[i] = Cpal;
                return;
            }
        }
    }


}

void PlayerPalsManager::SetSelPal(int selPal)
{
    this->selPal = selPal;
}
