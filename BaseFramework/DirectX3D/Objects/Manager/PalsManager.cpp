#include "Framework.h"

PalsManager::PalsManager()
{
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

bool PalsManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    Contact contact;
    float minDistance = FLT_MAX;
    for (Pal* pal : pals)
    {
        //외부에서 온 광선과 로봇이 충돌하면...
        if (pal->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //로봇마다 접점 정보 모두 갱신
            {
                minDistance = contact.distance; // 갱신정보 계속 반영
                hitPoint = contact.hitPoint;
            }
        }
    }
    return minDistance != FLT_MAX; // 충돌 확인 됐으면 리턴
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
    //pal->Scale() *= 0.01f;
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    palsInstancing.push_back(pal);
}

void PalsManager::Collision()
{
    for (Pal* pal : pals)
    {
        // 조건에따라 데미지 호출
        if (false) // 
        {
            pal->Damage();
            return;
        }
    }
}

void PalsManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    //생성거리 계수와 함께 표적의 주위에서 생성을 한다
    Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 30);
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
