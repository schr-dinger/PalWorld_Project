#include "Framework.h"

PlayerPalsManager::PlayerPalsManager()
{
    terrain = nullptr;
    target = nullptr;

    selPal = -1;

    InsertAllMAI(); // 모든 팔 모델 인스턴싱 생성

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
}

PlayerPalsManager::~PlayerPalsManager()
{
    for (Pal* pal : pals)
        delete pal;

    FOR(2)
        delete blendState[i];
}

void PlayerPalsManager::Update()
{
    OnGround(terrain);

    // 충돌 판정 진행
    Collision();

    // 소환한 펠만 업데이트
    if (selPal != -1)
    {
        palsMAI[pals[selPal]->name]->Update();

        pals[selPal]->Update();
    }
    

}

void PlayerPalsManager::Render()
{
    // 소환한 팔만 활성화, 모션 랜더(현재는 한 마리만 소환)

    if (selPal != -1)
    {
        blendState[1]->SetState(); // 투명도 적용
        palsMAI[pals[selPal]->name]->Render();
        blendState[0]->SetState();

        pals[selPal]->Render();
    }
}

void PlayerPalsManager::PostRender()
{
    if (selPal != -1)
    {
        pals[selPal]->PostRender();
    }
}

void PlayerPalsManager::GUIRender()
{
}

void PlayerPalsManager::SetTarget(Transform* target)
{
    this->target = target; // 매니저 입장에서 기록할 표적 : 일괄설정 등이 필요할 때 쓸 것
    // 아마 필요 없을 듯

    if (selPal != -1)
    {
        // 팔이 셋타겟하는 조건 추가하기
        //if () // 거리라든지(선공), 공격당했을때 등
        pals[selPal]->SetTarget(target);
    }

}

void PlayerPalsManager::SetPlayer(Player* player)
{
    player = this->player;
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
    return minDistance != FLT_MAX; // 충돌 확인 됐으면 리턴
    return false; // 거리 갱신 안되면 충돌 실패
}

void PlayerPalsManager::OnGround(Terrain* terrain)
{
    
    if (selPal != -1)
    {
        pals[selPal]->GetTransform()->Pos().y = terrain->GetHeight(pals[selPal]->GetTransform()->GlobalPos());
    }
}

void PlayerPalsManager::InsertAllMAI()
{
    // 펭키 모델 인스턴싱 넣기
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
    palsMAIIndex.insert({ "펭키", 0 }); // 모델 인스턴스 인덱스용 map에도 추가
                                        // "펭키"라는 key(모델 인스턴싱)를 가진 인덱스 값(0번부터),
                                        // 같은 팔을 잡을 때마다 인덱스 값 증가(같은 팔이라도 인덱스가 달라 다른 개체)

    // 팔 추가시 추가 작업 할 곳 ----------------------
}

void PlayerPalsManager::Collision()
{
    if (selPal != -1)
    {
        // 조건에따라 데미지 호출
        if (false) // 현재 맞는 조건 없음
        {
            pals[selPal]->Damage();
        }
    }
}

void PlayerPalsManager::Summons()
{
    if (selPal == -1) return;
    pals[selPal]->Summons(player->GlobalPos() + player->Back() * 5 ); // 일단은 플레이어 앞에 
    // * 추후 컴퓨트피킹으로 크로스헤어가 가리키는 곳으로 수정해야 함
}

void PlayerPalsManager::Caught(Pal* CaughtPal)
{
    // 팩터리 패턴 구현해야 함, 현재는 구현 안하고 새로 만들기
    if (CaughtPal->name == "펭키")
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Penguin(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);
        // *새로 만든 팔과, 잡은 팔의 체력, 레벨, 공격력 등 스펙 똑같이 넣어줘야 함 
        //  -> 팩토리 패턴 구현때 넣기, 현재는 같은 개체의 새로운 팔 생성

        palsMAIIndex[CaughtPal->name]++;// 해당 모델 인스턴싱 인덱스 증가
        pals.push_back(pal);
    }
    //else if (CaughtPal->name == "") // 잡을 다른 팔이 있다면 여기서
    //{
    //
    //}

}
