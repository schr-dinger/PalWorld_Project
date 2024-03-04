#include "Framework.h"

PalsManager::PalsManager()
{
    // 240224 테스트 : map으로 모든 펠 모델인스턴싱르로 만들어준 뒤(모델과 각 모델이 가지고 있는 모션들까지)
    //                 팰 트랜스폼만 넣어주기 -> 마이 팔 매니저에만 하면 될듯


    // 여기서부터
    InsertMAI("PenGuin");                   // 공용 : 아이들, 걷기, 런, 공격, 데미지
    palsInstancing[0]->ReadClip("Work");    // 추가 모션
    palsInstancing[0]->SetTag("Penguin");

    FOR(SIZE)
    {
        Transform* transform = palsInstancing[0]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal);
    }
    // 여기까지가 팔 하나

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);

    // 테스트 : 히트
    testHit = {};
    testIsHit = false;
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

    // 충돌 판정 진행
    Collision();

    // 리스폰
    time += DELTA; //경과시간 누적

    if (time >= SPAWN_TIME) //경과 시간이 생성간격에 도달하면
    {
        time -= SPAWN_TIME;
        Spawn(); //생성(스폰)
    }

    // 모델 업데이트
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal에서 버츄얼로 구현했지만, 
                       // 적용안되면 기본 함수로 바꾸기

    
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

    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->GUIRender();

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
        //pal->GetTransform()->Pos().y = terrain->GetHeightCompute(pal->GetTransform()->GlobalPos());
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

void PalsManager::InsertAllMAI()
{
    ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("PenGuin");
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    pal->ReadClip("Work");
    pal->SetTag("Penguin");
    palsMAI.insert({ "펭키", pal });                                     // 넣는 법 1.
    //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("펭키", pal)); // 넣는 법 2.
    FOR(SIZE)
    {
        Transform* transform = palsInstancing[0]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal);
    }


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

    // 테스트
    for (Pal* pal : pals)
    {
                     
        if (BulletManager::Get()->isCollision(pal->GetCollider()))
        {

            pal->Damage();

            return;
        }
    }

    if (testIsHit) // 포획이든 공격이든 맞았으면 활성
    {
        for (Pal* pal : pals)
        {
            if (pal->GetCollider()->IsCollision(player->GetPalSpearCol()))
            {
                // 여기 들어오면 팔스피어 맞은 개체, 플레이어 팔매니저에 해당 팔 깊은 복사
                PlayerPalsManager::Get()->Caught(pal);
                // 이후 죽음처리(지금은 단순 트랜스폼 비활성화), 나중에 다시 스폰될 것
                pal->GetTransform()->SetActive(false);
                return; //팔스피어(포획)에 맞았여기서 리턴
            }

            // 테스트
            if (BulletManager::Get()->isCollision(pal->GetCollider()))
            {
               
                pal->Damage();

                return; 
            }


        }

       

        // 포획이 아니라면 맞기
        pals[hitPalIndex]->Damage();
        testIsHit = false;
    }
    
    
}

void PalsManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    //생성거리 계수와 함께 표적의 주위에서 생성을 한다
    Vector3 randomPos;
    if (target == nullptr) // 타겟 없는 경우 테스트
    {
        randomPos = (dir.GetNormalized() * 20);
    }
    else
    {
        randomPos = target->Pos() + (dir.GetNormalized() * 20);

    }
    randomPos.y = 0;

    // 위에서 정해진 랜덤 장소에서 로봇 하나 생성 (선착순)
    for (Pal* pal : pals)
    {
        if (!pal->GetTransform()->Active()) // 로봇을 조회 중인데 비활성화 중인 개체가 있으면
        {
            pal->Spawn(randomPos); // 개별 로봇 호출
            return; //반복문(생성 절차) 종료
        }
    }
}
