#include "Framework.h"

PalsManager::PalsManager()
{
    
    // ���⼭����
    InsertMAI("PenGuin");                   // ���� : ���̵�, �ȱ�, ��, ����, ������
    palsInstancing[0]->ReadClip("Work");    // �߰� ���
    palsInstancing[0]->SetTag("Penguin");
    //palsInstancing[0]->GetMaterial(1)->SetDiffuseMap(L"Textures/Color/White.png");
    FOR(penguinN)
    {
        Transform* transform = palsInstancing[0]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal);
    }
    // ��������� �� �ϳ�

    InsertMAI("Mammoth");                   // ���� : ���̵�, �ȱ�, ��, ����, ������
                                            // �߰� ���
    palsInstancing[1]->SetTag("mammoth");
    FOR(mammothN)
    {
        Transform* transform = palsInstancing[1]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;
        Pal* pal = new Mammoth(transform, palsInstancing[1], i);
        pals.push_back(pal);
    }


    InsertMAI("DarkWolf");                   // ���� : ���̵�, �ȱ�, ��, ����, ������
                                        // �߰� ���
    palsInstancing[2]->SetTag("wolf");
    FOR(wolfN)
    {
        Transform* transform = palsInstancing[2]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;
        Pal* pal = new DarkWolf(transform, palsInstancing[2], i);
        pals.push_back(pal);
    }



    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);

    lastPos.resize(pals.size());

    // ���� �ʵ忡 ��ȯ
    FOR(pals.size())
    {
        Spawn();
    }
    // �� ������Ʈ
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update();

    // �׽�Ʈ : ��Ʈ
    testHit = {};
    testIsHit = false;
    //palsInstancing[1]->GetMaterial(0)->SetDiffuseMap(L"Textures/Color/White.png");
    //palsInstancing[1]->GetMaterial(1)->SetDiffuseMap(L"Textures/Color/White.png");
}

PalsManager::~PalsManager()
{
    for (ModelAnimatorInstancing* pal : palsInstancing)
        delete pal;


    for (Pal* pal : pals)
        delete pal;

    FOR(2)
        delete blendState[i];
}

void PalsManager::Update()
{
    OnGround(terrain);

    FOR(pals.size())
    {
        lastPos[i] = pals[i]->GetTransform()->GlobalPos();
    }

    // ������
    //time += DELTA; //����ð� ����
    //
    //if (time >= SPAWN_TIME) //��� �ð��� �������ݿ� �����ϸ�
    //{
    //    time -= SPAWN_TIME;
    //    Spawn(); //����(����)
    //}

    PathCollider();

    // �� ������Ʈ
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal���� ������ ����������, 
                       // ����ȵǸ� �⺻ �Լ��� �ٲٱ�

    // �浹 ���� ����
    Collision();

    if (KEY_DOWN('K') && !pals[0]->skill[0]->Active())
    {
        pals[0]->FieldAttack();
        //FieldAttack();
    }

}

void PalsManager::Render()
{
    blendState[1]->SetState(); // ���� ����
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Render();
    blendState[0]->SetState();

    for (Pal* pal : pals)
        pal->Render();

}

void PalsManager::PostRender()
{
    // ĳ���� UI����
    for (Pal* pal : pals)
        pal->PostRender();
}

void PalsManager::GUIRender()
{
    for (Pal* pal : pals)
        pal->GUIRender();

    //for (ModelAnimatorInstancing* pal : palsInstancing)
    //    pal->GUIRender();

}

void PalsManager::SetTarget(Transform* target)
{
    this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    //�� �κ� ���忡���� ǥ���� ���� ����
    for (Pal* pal : pals)
    {
        // ���� ��Ÿ���ϴ� ���� �߰��ϱ�
        //if () // �Ÿ������(����), ���ݴ������� ��
        pal->SetTarget(target);
    }
}

void PalsManager::SetPlayer(Player* player)
{
    this->player = player;
}

bool PalsManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    Contact contact;
    float minDistance = FLT_MAX;
    int tmp = 0;
    for (Pal* pal : pals)
    {
        //�ܺο��� �� ������ �κ��� �浹�ϸ�...
        if (pal->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //�κ����� ���� ���� ��� ����
            {
                minDistance = contact.distance; // �������� ��� �ݿ�
                hitPoint = contact.hitPoint;
                hitPalIndex = tmp;
            }
        }
        tmp++;
    }
    if (minDistance != FLT_MAX) // �浹 Ȯ�� ������ ����
    {
        // �׽�Ʈ : ��Ʈ
        testHit = hitPoint;
        testIsHit = true;

        return true; 
    }
    return false; // �Ÿ� ���� �ȵǸ� �浹 ����
}

void PalsManager::OnGround(Terrain* terrain)
{
    for (Pal* pal : pals)
    {
        pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
    }
}

void PalsManager::InsertMAI(string palModelName)
{
    ModelAnimatorInstancing* pal = new ModelAnimatorInstancing(palModelName);
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    palsInstancing.push_back(pal);
}


void PalsManager::Collision()
{
    //for (Pal* pal : pals)
    //{
    //    // ���ǿ����� ������ ȣ��
    //    if (false) // 
    //    {
    //        pal->Damage();
    //        return;
    //    }
    //}


    for (int i = 0; i < pals.size(); i++)
    {
        for (int j = 0; j < pals.size(); j++)
        {
            if (i == j) continue;
            if (pals[i]->GetCollider()->IsCollision(pals[j]->GetCollider()))
            {
                Vector3 nol = (pals[i]->GetTransform()->GlobalPos() - pals[j]->GetTransform()->GlobalPos()).GetNormalized();
                Vector3 dir = pals[i]->GetTransform()->GlobalPos() - lastPos[i];
                if (dir == Vector3(0.0f, 0.0f, 0.0f)) continue;
                Vector3 tmpV1 = pals[i]->GetTransform()->Back();
                Vector3 tmpV2 = pals[j]->GetTransform()->GlobalPos() - pals[i]->GetTransform()->GlobalPos();
                if (Dot(tmpV1, tmpV2) <= 0.0f) continue;
                Vector3 mDir = dir * -1;
                //Vector3 tmp = 2 * nol * Dot(mDir, nol);
                Vector3 tmp = nol * Dot(mDir, nol);
                Vector3 fDir = dir + tmp;
                pals[i]->GetTransform()->Pos() = lastPos[i] + fDir;
                pals[i]->GetTransform()->UpdateWorld();
            }
        }


    }


    for (Pal* pal : pals) 
    {
        if (PalSpearManager::Get()->IsCollision(pal->GetCollider(), pal) && pal->isInvincible == false) // �ӽ��Ǿ��� �ݸ����� �ҷ��ͼ�, ��� �ӽ��Ǿ�� ��� �ʵ� ���� �浹�˻�
        {
            // ���� ������ �Ƚ��Ǿ� ���� ��ü, �÷��̾� �ȸŴ����� �ش� �� ���� ����
            //PlayerPalsManager::Get()->Caught(pal);
            //// ���� ����ó��(������ �ܼ� Ʈ������ ��Ȱ��ȭ), ���߿� �ٽ� ������ ��
            //pal->GetTransform()->SetActive(false);

            // �������� 240311�η� �ӽ��Ǿ� �Ŵ�������
            //pal->GetCollider()->SetActive(false); 
            // �ӽ��Ǿ �´� ���� ���� �ȴ��ϰ� �ϱ�
            pal->isInvincible = true;

            return; //�Ƚ��Ǿ�(��ȹ)�� �¾ҿ��⼭ ����
        }
        else if (MyPalSkillManager::Get()->IsCollision(pal->GetCollider()) && pal->isInvincible == false) // �ӽ��Ǿ ���� �ʰ� �� �� ��ų�� �¾Ҵٸ� �±�
        {
            pal->Damage();
            return;
        }

    }

    if (testIsHit) // �¾����� Ȱ��
    {
        // �±�
        pals[hitPalIndex]->Damage();
        testIsHit = false;
    }
    
    
}

void PalsManager::Spawn()
{
    Vector3 dir;
    dir.x = RANDOM->Float(-1.0f, 1.0f);
    dir.z = RANDOM->Float(-1.0f, 1.0f);

    //�����Ÿ� ����� �Բ� ǥ���� �������� ������ �Ѵ�
    Vector3 randomPos;
    if (target == nullptr) // Ÿ�� ���� ��� �׽�Ʈ
    {
        randomPos = Vector3(100.0f,0.0f,100.0f) + (dir.GetNormalized() * 20);
    }
    else
    {
        randomPos = target->Pos() + (dir.GetNormalized() * 20);

    }
    randomPos.y = 0;


    // ������ ������ ���� ��ҿ��� �κ� �ϳ� ���� (������)
    for (Pal* pal : pals)
    {
        Vector3 randomPos1;
        randomPos1 = Vector3(250.0f, 0.0f, 250.0f) + Vector3(RANDOM->Float(-200.0f, 200.0f), 0, RANDOM->Float(-200.0f, 200.0f));
        Vector3 randomPos2;
        randomPos2 = Vector3(375.0f, 0.0f, 375.0f) + Vector3(RANDOM->Float(-20.0f, 20.0f), 0, RANDOM->Float(-20.0f, 20.0f));
        Vector3 randomPos3;
        randomPos3 = Vector3(250.0f, 0.0f, 125.0f) + Vector3(RANDOM->Float(-50.0f, 50.0f), 0, RANDOM->Float(-50.0f, 50.0f));

        if (!pal->GetTransform()->Active()) // �κ��� ��ȸ ���ε� ��Ȱ��ȭ ���� ��ü�� ������
        {
            //pal->Spawn(randomPos); // ���� �κ� ȣ��
            //return; //�ݺ���(���� ����) ����

            if (pal->name == "��Ű")
            {
                pal->Spawn(randomPos1);
            }
            else if (pal->name == "�׸���")
            {
                pal->Spawn(randomPos2);
            }
            else if (pal->name == "��ũ����")
            {
                pal->Spawn(randomPos3);
            }

        }
    }
}

void PalsManager::PathCollider()
{
    if (target == nullptr) return;

    for (Pal* pal : pals)
    {
        if (Distance(pal->GetTransform()->GlobalPos(), target->GlobalPos()) < 30.0f)
        {
            Vector3 cPos;
            if (LandScapeManager::Get()->CheckPalCollision(pal->GetCollider(), cPos))
            {
                Vector3 normal = -(cPos - pal->GetTransform()->Pos()).GetNormalized();

                    pal->GetTransform()->Pos() = Lerp(pal->GetTransform()->Pos(), pal->GetTransform()->Pos() + normal * 0.1f, 0.5f);
            }
        }
    }
}
