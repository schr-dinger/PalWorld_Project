#include "Framework.h"

PalsManager::PalsManager()
{
    
    // 여기서부터
    InsertMAI("PenGuin");                   // 공용 : 아이들, 걷기, 런, 공격, 데미지
    palsInstancing[0]->ReadClip("Work");    // 추가 모션
    palsInstancing[0]->SetTag("Penguin");
    //palsInstancing[0]->GetMaterial(1)->SetDiffuseMap(L"Textures/Color/White.png");
    FOR(penguinN)
    {
        Transform* transform = palsInstancing[0]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal);
    }
    // 여기까지가 팔 하나

    InsertMAI("Mammoth");                   // 공용 : 아이들, 걷기, 런, 공격, 데미지
                                            // 추가 모션
    palsInstancing[1]->SetTag("mammoth");
    FOR(mammothN)
    {
        Transform* transform = palsInstancing[1]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;
        Pal* pal = new Mammoth(transform, palsInstancing[1], i);
        pals.push_back(pal);
    }


    InsertMAI("DarkWolf");                   // 공용 : 아이들, 걷기, 런, 공격, 데미지
                                        // 추가 모션
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

    // 전부 필드에 소환
    FOR(pals.size())
    {
        Spawn();
    }
    // 모델 업데이트
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update();

    // 테스트 : 히트
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

    // 리스폰
    //time += DELTA; //경과시간 누적
    //
    //if (time >= SPAWN_TIME) //경과 시간이 생성간격에 도달하면
    //{
    //    time -= SPAWN_TIME;
    //    Spawn(); //생성(스폰)
    //}

    PathCollider();

    // 모델 업데이트
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal에서 버츄얼로 구현했지만, 
                       // 적용안되면 기본 함수로 바꾸기

    // 충돌 판정 진행
    Collision();

    if (KEY_DOWN('K') && !pals[0]->skill[0]->Active())
    {
        pals[0]->FieldAttack();
        //FieldAttack();
    }

}

void PalsManager::Render()
{
    blendState[1]->SetState(); // 투명도 적용
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Render();
    blendState[0]->SetState();

    for (Pal* pal : pals)
        pal->Render();

}

void PalsManager::PostRender()
{
    // 캐릭터 UI랜더
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
    this->target = target; // 매니저 입장에서 기록할 표적 : 일괄설정 등이 필요할 때 쓸 것
    //각 로봇 입장에서의 표적도 지금 설정
    for (Pal* pal : pals)
    {
        // 팔이 셋타겟하는 조건 추가하기
        //if () // 거리라든지(선공), 공격당했을때 등
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
        //외부에서 온 광선과 로봇이 충돌하면...
        if (pal->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //로봇마다 접점 정보 모두 갱신
            {
                minDistance = contact.distance; // 갱신정보 계속 반영
                hitPoint = contact.hitPoint;
                hitPalIndex = tmp;
            }
        }
        tmp++;
    }
    if (minDistance != FLT_MAX) // 충돌 확인 됐으면 리턴
    {
        // 테스트 : 히트
        testHit = hitPoint;
        testIsHit = true;

        return true; 
    }
    return false; // 거리 갱신 안되면 충돌 실패
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
    //    // 조건에따라 데미지 호출
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
        if (PalSpearManager::Get()->IsCollision(pal->GetCollider(), pal) && pal->isInvincible == false) // 팰스피어의 콜리전을 불러와서, 모든 팰스피어와 모든 필드 팰을 충돌검사
        {
            // 여기 들어오면 팔스피어 맞은 개체, 플레이어 팔매니저에 해당 팔 깊은 복사
            //PlayerPalsManager::Get()->Caught(pal);
            //// 이후 죽음처리(지금은 단순 트랜스폼 비활성화), 나중에 다시 스폰될 것
            //pal->GetTransform()->SetActive(false);

            // 위과정은 240311부로 팰스피어 매니저에서
            //pal->GetCollider()->SetActive(false); 
            // 팰스피어에 맞는 순간 공격 안당하게 하기
            pal->isInvincible = true;

            return; //팔스피어(포획)에 맞았여기서 리턴
        }
        else if (MyPalSkillManager::Get()->IsCollision(pal->GetCollider()) && pal->isInvincible == false) // 팰스피어에 맞지 않고 내 팰 스킬에 맞았다면 맞기
        {
            pal->Damage();
            return;
        }

    }

    if (testIsHit) // 맞았으면 활성
    {
        // 맞기
        pals[hitPalIndex]->Damage();
        testIsHit = false;
    }
    
    
}

void PalsManager::Spawn()
{
    Vector3 dir;
    dir.x = RANDOM->Float(-1.0f, 1.0f);
    dir.z = RANDOM->Float(-1.0f, 1.0f);

    //생성거리 계수와 함께 표적의 주위에서 생성을 한다
    Vector3 randomPos;
    if (target == nullptr) // 타겟 없는 경우 테스트
    {
        randomPos = Vector3(100.0f,0.0f,100.0f) + (dir.GetNormalized() * 20);
    }
    else
    {
        randomPos = target->Pos() + (dir.GetNormalized() * 20);

    }
    randomPos.y = 0;


    // 위에서 정해진 랜덤 장소에서 로봇 하나 생성 (선착순)
    for (Pal* pal : pals)
    {
        Vector3 randomPos1;
        randomPos1 = Vector3(250.0f, 0.0f, 250.0f) + Vector3(RANDOM->Float(-200.0f, 200.0f), 0, RANDOM->Float(-200.0f, 200.0f));
        Vector3 randomPos2;
        randomPos2 = Vector3(375.0f, 0.0f, 375.0f) + Vector3(RANDOM->Float(-20.0f, 20.0f), 0, RANDOM->Float(-20.0f, 20.0f));
        Vector3 randomPos3;
        randomPos3 = Vector3(250.0f, 0.0f, 125.0f) + Vector3(RANDOM->Float(-50.0f, 50.0f), 0, RANDOM->Float(-50.0f, 50.0f));

        if (!pal->GetTransform()->Active()) // 로봇을 조회 중인데 비활성화 중인 개체가 있으면
        {
            //pal->Spawn(randomPos); // 개별 로봇 호출
            //return; //반복문(생성 절차) 종료

            if (pal->name == "펭키")
            {
                pal->Spawn(randomPos1);
            }
            else if (pal->name == "그린모스")
            {
                pal->Spawn(randomPos2);
            }
            else if (pal->name == "다크울프")
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
