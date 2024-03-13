#include "Framework.h"

PlayerPalsManager::PlayerPalsManager()
{
    terrain = nullptr;
    target = nullptr;

    selPal = -1;

    pals.resize(100);

    InsertAllMAI(); // ��� �� �� �ν��Ͻ� ����(���� "��Ű" �ϳ�,)
    FOR(2)
    {
        Transform* transform = palsMAI["��Ű"]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Penguin(transform, palsMAI["��Ű"], palsMAIIndex["��Ű"]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
        palsMAIIndex["��Ű"]++;// �ش� �� �ν��Ͻ� �ε��� ����
        //pals.push_back(pal);
        pals[i] = pal;
        
    }
    
    FOR(2)
    {
        Transform* transform = palsMAI["�׸���"]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Mammoth(transform, palsMAI["�׸���"], palsMAIIndex["�׸���"]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
        palsMAIIndex["�׸���"]++;// �ش� �� �ν��Ͻ� �ε��� ����
        //pals.push_back(pal);
        pals[i+2] = pal;

    }

    FOR(2)
    {
        Transform* transform = palsMAI["��ũ����"]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new DarkWolf(transform, palsMAI["��ũ����"], palsMAIIndex["��ũ����"]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����
        palsMAIIndex["��ũ����"]++;// �ش� �� �ν��Ͻ� �ε��� ����
        //pals.push_back(pal);
        pals[i + 4] = pal;

    }


    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
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
}

void PlayerPalsManager::Update()
{
    OnGround(terrain);

    // �浹 ���� ����
    Collision();



    // ��ȯ�� �縸 ������Ʈ, �� �� �ν��Ͻ��� �̸� ��� ������Ʈ
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        iter->second->Update();
    }
    for (Pal* pal : pals)
    {
        if (pal == nullptr)
        {
            continue;
        }


        pal->Update();
    }

    if (selPal != -1)
    {
        PathFinding();
        Move();
        //palsMAI[pals[selPal]->name]->Update();
        //pals[selPal]->Update();
        if (KEY_DOWN('L') && !pals[selPal]->skill[0]->Active())
        {
            pals[selPal]->Attack();
        }
    }
    

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
    for (Pal* pal : pals)
    {

        if (pal == nullptr)
        {
            continue;
        }
        pal->Render();
    }


    // ��ȯ�� �ȸ� Ȱ��ȭ, ��� ����(����� �� ������ ��ȯ)

    //if (selPal != -1)
    //{
    //    blendState[1]->SetState(); // ���� ����
    //    palsMAI[pals[selPal]->name]->Render();
    //    blendState[0]->SetState();
    //
    //    pals[selPal]->Render();
    //}
}

void PlayerPalsManager::PostRender()
{
    //if (selPal != -1)
    //{
    //    pals[selPal]->PostRender();
    //}
    for (Pal* pal : pals)
    {
        if (pal != nullptr)
        {
            pal->PostRender();
        }
    }
}

void PlayerPalsManager::GUIRender()
{
    ImGui::Text("MyPalsSIze : %d", pals.size());
    ImGui::Text("pathsize : %d", path.size());

    ImGui::Text("destPosX : %f", destPos.x);
    ImGui::Text("destPosY : %f", destPos.y);
    ImGui::Text("destPosZ : %f", destPos.z);

    if (selPal != -1)
    {
        //ImGui::Text("X: %f", pals[selPal]->GetTransform()->GlobalPos().x);
        //ImGui::Text("y: %f", pals[selPal]->GetTransform()->GlobalPos().y);
        //ImGui::Text("z: %f", pals[selPal]->GetTransform()->GlobalPos().z);
    }

    if (path.size() > 0)
    {
        ImGui::Text("X: %f", path.back().x);
        ImGui::Text("y: %f", path.back().y);
        ImGui::Text("z: %f", path.back().z);
        ImGui::Text("X: %f", destPos.x);
        ImGui::Text("y: %f", destPos.y);
        ImGui::Text("z: %f", destPos.z);
    }


}

void PlayerPalsManager::SetTarget(Transform* target)
{
    this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    // �Ƹ� �ʿ� ���� ��

    if (selPal != -1)
    {
        // ���� ��Ÿ���ϴ� ���� �߰��ϱ�
        //if () // �Ÿ������(����), ���ݴ������� ��
        pals[selPal]->SetTarget(target);
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
            pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
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


    for (Pal* pal : pals)
    {
        if (pal != nullptr)
        {
            // ���ǿ����� ������ ȣ��
            if (FieldPalSkillManager::Get()->IsCollision(pal->GetCollider())) // �ʵ� ��ų�� �¾��� ��
            {
                pal->Damage();
            }
        }
    }

}

void PlayerPalsManager::PathFinding()
{
    if (pals[selPal] == nullptr) return;

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
        //destPos = CAM->GlobalPos();

        //destPos = player->GlobalPos();

        if (AStarManager::Get()->GetAStar()->IsCollisionObstacle(pals[selPal]->GetTransform()->GlobalPos(), destPos))
        {
            SetPath();
        }
        else
        {
            path.clear();
            path.push_back(destPos);
        }

        pathTime = 0.0f;
    }
}

void PlayerPalsManager::SetPath()
{
    int startIndex = AStarManager::Get()->GetAStar()->FindCloseNode(pals[selPal]->GetTransform()->GlobalPos());
    int endIndex = AStarManager::Get()->GetAStar()->FindCloseNode(destPos);

    AStarManager::Get()->GetAStar()->GetPath(startIndex, endIndex, path); // ���� �� ���� path ���Ϳ� ����
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

void PlayerPalsManager::Summons()
{
    if (selPal == -1) return;
    pals[selPal]->isSpawned = true;
    pals[selPal]->Summons(player->GlobalPos() + player->Back() * 5 ); // �ϴ��� �÷��̾� �տ� 
    // * ���� ��ǻƮ��ŷ���� ũ�ν��� ����Ű�� ������ �����ؾ� ��
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
