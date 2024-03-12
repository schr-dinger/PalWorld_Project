#include "Framework.h"

PlayerPalsManager::PlayerPalsManager()
{
    terrain = nullptr;
    target = nullptr;

    selPal = -1;

    pals.resize(100);

    InsertAllMAI(); // 모든 팔 모델 인스턴싱 생성(현재 "펭키" 하나,)
    FOR(3)
    {
        Transform* transform = palsMAI["펭키"]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Penguin(transform, palsMAI["펭키"], palsMAIIndex["펭키"]);
        // *새로 만든 팔과, 잡은 팔의 체력, 레벨, 공격력 등 스펙 똑같이 넣어줘야 함 
        //  -> 팩토리 패턴 구현때 넣기, 현재는 같은 개체의 새로운 팔 생성
        palsMAIIndex["펭키"]++;// 해당 모델 인스턴싱 인덱스 증가
        //pals.push_back(pal);
        pals[i] = pal;
        
    }
    
    FOR(3)
    {
        Transform* transform = palsMAI["그린모스"]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* pal = new Mammoth(transform, palsMAI["그린모스"], palsMAIIndex["그린모스"]);
        // *새로 만든 팔과, 잡은 팔의 체력, 레벨, 공격력 등 스펙 똑같이 넣어줘야 함 
        //  -> 팩토리 패턴 구현때 넣기, 현재는 같은 개체의 새로운 팔 생성
        palsMAIIndex["그린모스"]++;// 해당 모델 인스턴싱 인덱스 증가
        //pals.push_back(pal);
        pals[i+3] = pal;

    }



    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
}

PlayerPalsManager::~PlayerPalsManager()
{
    // 모델 인스턴싱 삭제
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

    // 충돌 판정 진행
    Collision();



    // 소환한 펠만 업데이트, 단 모델 인스턴싱은 미리 계속 업데이트
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
    // 테스트 : 모두 활성화
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
    {
        blendState[1]->SetState(); // 투명도 적용

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


    // 소환한 팔만 활성화, 모션 랜더(현재는 한 마리만 소환)

    //if (selPal != -1)
    //{
    //    blendState[1]->SetState(); // 투명도 적용
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
    return minDistance != FLT_MAX; // 충돌 확인 됐으면 리턴
    return false; // 거리 갱신 안되면 충돌 실패
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
    }
    // 팔 추가시 추가 작업 할 곳 ----------------------

    {
        ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("Mammoth");
        pal->ReadClip("Idle");
        pal->ReadClip("Walk");
        pal->ReadClip("Run");
        pal->ReadClip("Attack");
        pal->ReadClip("Damage");
        pal->SetTag("mammoth");
        palsMAI.insert({ "그린모스", pal });                                     // 넣는 법 1.
        //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("펭키", pal)); // 넣는 법 2.
        palsMAIIndex.insert({ "그린모스", 0 }); // 모델 인스턴스 인덱스용 map에도 추가
                                            // "펭키"라는 key(모델 인스턴싱)를 가진 인덱스 값(0번부터),
                                            // 같은 팔을 잡을 때마다 인덱스 값 증가(같은 팔이라도 인덱스가 달라 다른 개체)
    }
}

void PlayerPalsManager::Collision()
{
    //if (selPal != -1)
    //{
    //    // 조건에따라 데미지 호출
    //    if (FieldPalSkillManager::Get()->IsCollision(pals[selPal]->GetCollider())) // 필드 스킬에 맞았을 때
    //    {
    //        pals[selPal]->Damage();
    //    }
    //}


    for (Pal* pal : pals)
    {
        if (pal != nullptr)
        {
            // 조건에따라 데미지 호출
            if (FieldPalSkillManager::Get()->IsCollision(pal->GetCollider())) // 필드 스킬에 맞았을 때
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

    AStarManager::Get()->GetAStar()->GetPath(startIndex, endIndex, path); // 길을 낸 다음 path 벡터에 저장
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
        Pal* Cpal = new Penguin(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);
        // *새로 만든 팔과, 잡은 팔의 체력, 레벨, 공격력 등 스펙 똑같이 넣어줘야 함 
        //  -> 팩토리 패턴 구현때 넣기, 현재는 같은 개체의 새로운 팔 생성

        palsMAIIndex[CaughtPal->name]++;// 해당 모델 인스턴싱 인덱스 증가
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
    else if (CaughtPal->name == "그린모스") // 잡을 다른 팔이 있다면 여기서
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// 사이즈 조절은 여기서
        Pal* Cpal = new Mammoth(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);

        palsMAIIndex[CaughtPal->name]++;// 해당 모델 인스턴싱 인덱스 증가
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
