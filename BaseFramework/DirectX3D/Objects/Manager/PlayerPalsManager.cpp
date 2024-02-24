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

    // 모델 업데이트
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal에서 버츄얼로 구현했지만, 
                       // 적용안되면 기본 함수로 바꾸기
}

void PlayerPalsManager::Render()
{
    blendState[1]->SetState(); // 투명도 적용
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
        iter->second->Render();
    blendState[0]->SetState();

    for (Pal* pal : pals)
    {
        //if (pal->acti)
        //{
        //
        //}
        pal->Render();

    }
}

void PlayerPalsManager::PostRender()
{
    // 캐릭터 UI랜더
    for (Pal* pal : pals)
        pal->PostRender();
}

void PlayerPalsManager::GUIRender()
{
}

void PlayerPalsManager::SetTarget(Transform* target)
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

void PlayerPalsManager::SetPlayer(Player* player)
{
    player = this->player;
}

bool PlayerPalsManager::IsCollision(Ray ray, Vector3& hitPoint)
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

void PlayerPalsManager::OnGround(Terrain* terrain)
{
    for (Pal* pal : pals)
    {
        pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
    }
}

void PlayerPalsManager::InsertAllMAI()
{
}

void PlayerPalsManager::Collision()
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

void PlayerPalsManager::Summons()
{
    if (selPal == -1) return;
    pals[selPal]->Summons(player->GlobalPos() + player->Back() * 5 ); // 일단은 플레이어 앞에 
    // * 추후 컴퓨트피킹으로 크로스헤어가 가리키는 곳으로 수정해야 함
}
