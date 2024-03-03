#include "Framework.h"

Penguin::Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    :transform(transform), instancing(instancing), index(index)
{
    name = "펭키";
    speed = 5; //속력 : 기본 스탯
    maxHP = 100;
    curHP = 100;

    // 부모에서 가져온 스킬 세팅
    skill[0] = new Tornado();
    skill[0]->Setpal(this); // 스킬 시작 위치 받아가는 함수, 이 팔의 위치에서
    skill[0]->SetSkill();   // 스킬 세팅(시작 위치), 

    root = new Transform(); // 콜라이더가 위치할 장소(위치)

    //충돌체
    collider = new CapsuleCollider(35, 20); // 사이즈
    collider->SetParent(root);
    collider->Rot().z = XMConvertToRadians(90.0f);
    collider->Pos() = { 10, 0, 0 };
    collider->SetActive(true); //충돌체 보이기 싫을 때는 이 부분 false

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //모델이 가진 동작 숫자만큼 이벤트 리사이징
    eventIters.resize(instancing->GetClipSize());

    //이벤트 세팅
    SetEvent((int)ACTION::ATTACK, bind(&Penguin::EndAttack, this), 1.5f);
    SetEvent((int)ACTION::DAMAGE, bind(&Penguin::EndDamage, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // 등록되어 있을 이벤트의 시작지점으로 반복자 설정
    }

    //캐릭터 UI 추가
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
    hpBar->SetActive(false);

    tmpN = 0;

    velocity = { 0, 0, 0 };
    target = nullptr;
}

Penguin::~Penguin()
{
    // 객체 삭제
    delete collider;
    delete root;

    // 임시 삭제
    delete transform;

    // 체력바 삭제
    delete hpBar;
}

void Penguin::Update()
{
    //활성화 시에만 업데이트
    if (!transform->Active()) return;
    //ClipSync();
    if (target)
    {
        velocity = target->GlobalPos() - transform->GlobalPos(); // 속력기준 : 표적과 자신의 거리
        Move(); //움직이기
    }

    ExecuteEvent(); // 이벤트가 터져야 하면 수행하기
    UpdateUI(); //UI 업데이트

    root->SetWorld(instancing->GetTransformByNode(index, 4));
    //root->SetWorld(instancing->GetTransformByNode(index, tmpN));
    collider->UpdateWorld(); //충돌체 업데이트

    //if (KEY_DOWN('Q'))
    //{
    //    tmpN++;
    //}
    //else if (KEY_DOWN('E'))
    //{
    //    tmpN = 0;;
    //
    //}

    // 스킬 테스트
    //if (KEY_DOWN('K') && !skill[0]->Active())
    //{
    //    Attack();
    //    //FieldAtack();
    //}
    skill[0]->Update();

}

void Penguin::Render()
{
    //활성화 시에만 업데이트
    if (!transform->Active()) return;
    collider->Render();
    skill[0]->Render();
}

void Penguin::PostRender()
{
    //활성화 시에만 업데이트
    if (!transform->Active()) return;
    if (velocity.Length() >= 15.0f) return;
    hpBar->Render();

    if (hpBar->Active())
    {
        Vector3 tmp = transform->Pos() + Vector3(0, 2.0f, 0);
        //tmp = CAM->WorldToScreen(tmp);
        tmp = hpBar->GlobalPos();
        tmp.y += 30.0f;
        string tmpString = name + " 테스트ㅁㄴㅇㄻㄴㅇㄻㅇㄴㄹㄴㅇㅁㄹㄴㅁㅇㄴㅇㄻ";
        Font::Get()->SetStyle("Default2");
        Font::Get()->RenderText(tmpString, { tmp.x, tmp.y });
        Font::Get()->SetStyle("Default");
    }
    
}

void Penguin::GUIRender()
{
    //활성화 시에만 업데이트
    if (!transform->Active()) return;
    ///collider->GUIRender();
    //ImGui::Text("Node : %d", &tmpN);
    //skill[0]->GUIRender();
}

void Penguin::Attack()
{
    // 모션 설정
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // 스킬 액티브
    skill[0]->SetActive(true);
    skill[0]->SetSkill();
    MyPalSkillManager::Get()->AddFieldSkill(skill[0]);

}

void Penguin::FieldAttack()
{
    // 모션 설정
    action = ACTION::ATTACK;
    instancing->PlayClip(index, (int)ACTION::ATTACK);
    eventIters[(int)ACTION::ATTACK] = totalEvent[(int)ACTION::ATTACK].begin();

    // 스킬 액티브
    skill[0]->SetActive(true);
    skill[0]->SetSkill();
    FieldPalSkillManager::Get()->AddFieldSkill(skill[0]);
}

void Penguin::Damage()
{
    // 무적이 되는 조건들
    if (action == ACTION::DAMAGE) return; // 맞고 있을 땐 안 맞는다.

    //체력에 -
    curHP -= 20;
    hpBar->SetAmount(curHP / maxHP); // 체력 비율에 따라 체력바 설정

    // 체력이 완전히 바닥나면
    if (curHP <= 0)
    {
        // 죽는 모션 있으면 세팅
        //SetAction(ACTION::DIE); 
        
        // 현재는 바로 비활성화
        transform->SetActive(false);
        return;//이 함수 종료
    }

    // 아직 안 죽었으면 산 로봇답게 맞는 동작 수행
    action = ACTION::DAMAGE;
    instancing->PlayClip(index, (int)ACTION::DAMAGE);
    eventIters[(int)ACTION::DAMAGE] = totalEvent[(int)ACTION::DAMAGE].begin();
}

void Penguin::Spawn(Vector3 pos)
{
    transform->SetActive(true); //비활성화였다면 활성화 시작
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // 소환 모션 있다면 소환모션부터
                             // 여기선 바로 아이들

    curHP = maxHP;
    hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;
}

void Penguin::Summons(Vector3 pos)
{
    transform->SetActive(true); //비활성화였다면 활성화 시작
    collider->SetActive(true);

    SetAction(ACTION::IDLE); // 
    hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;

}

void Penguin::SetTarget(Transform* target)
{
    this->target = target;
}

void Penguin::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0) return; // 선행 예약된 이벤트가 있으면 종료
    totalEvent[clip][timeRatio] = event;
}

void Penguin::ExecuteEvent()
{
    int index = (int)action; //현재 상태 받아오기
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //진행된 시간 나누기 전체 진행시간

    if (eventIters[index]->first > ratio) return; // 진행 시간이 정해진 기준에 못 미치면 종료(재시작)

    eventIters[index]->second(); //등록된 이벤트 수행
    eventIters[index]++;
}

void Penguin::EndAttack()
{
    SetAction(ACTION::IDLE);
}

void Penguin::EndDamage()
{
    SetAction(ACTION::IDLE); //맞았고, 안 죽었고, 움찔했으니 원래대로
}

void Penguin::SetAction(ACTION action)
{
    if (action == this->action) return; 

    this->action = action; //매개변수에 따라 상태 변화
    instancing->PlayClip(index, (int)action); //인스턴싱 내 자기 트랜스폼에서 동작 수행 시작
    eventIters[(int)action] = totalEvent[(int)action].begin();
}

void Penguin::Move()
{
    // 안움직이는 조건들
    if (action == ACTION::ATTACK) return; // 공격할 때는 움직이지 않음
    if (action == ACTION::DAMAGE) return; // 맞을 때는 움직이지 않음
    if (action == ACTION::WORK) return; // 작업할 때는 움직이지 않음
    //if (action == ACTION::) return; // 추가 가능

    if (velocity.Length() < 5)
    {
        speed = 0;
        SetAction(ACTION::IDLE);
    }
    //else if (velocity.Length() < 10)
    //{
    //    speed = 2;
    //    SetAction(ACTION::WALK);
    //}
    else if (velocity.Length() < 20) // 표적과 거리가 가까울 때는
    {
        speed = 4; //두 배로 빨라진다
        SetAction(ACTION::RUN);
    }
    else if (velocity.Length() < 30)
    {
        speed = 2;
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
    // 뒤 돌리기(모델 Back()이 실제로 앞

}

void Penguin::UpdateUI()
{
    //(모델이 바뀌면 이 숫자도 바꿀 것)
    barPos = transform->Pos() + Vector3(0, 1.8f, 0);

    if (!CAM->ContainPoint(barPos))
    {
        //hpBar->Scale() = {0, 0, 0};
        hpBar->SetActive(false);
        return;
    }

    if (!hpBar->Active()) hpBar->SetActive(true);

    // 뷰포트에 대한 함수를 호출하여 2D 이미지의 위치를 설정
    hpBar->Pos() = CAM->WorldToScreen(barPos); // 행렬 공간상의(=3D의) 물체를 뷰포트(=2D)에 투사
                                               // 이런 출력을 캔버싱이라고 한다

    float scale = 100 / velocity.Length(); // 임시 크기 변수를 지정해서, 표적과 트랜스폼의 거리에 따라
                                           // UI 크기가 최대 100픽셀까지 조절 가능

    scale = Clamp(0.1f, 1.0f, scale); // 최대 최소 범위를 다시 준다 (최대 범위 강제 가능)
                                      // 최초 계산의 크기를 살리고 싶다면 두 번째 매개변수를 더 많이 주면 된다


    // *추후 체력바, 다른 UI 스케일 고정 필요
    //hpBar->Scale() = { scale, scale, scale };
    hpBar->Scale() = { 0.3f, 0.3f, 0.3f };

    hpBar->UpdateWorld(); // 조정된 정점 업데이트
}

//void Penguin::ClipSync()
//{
//    if ((ACTION)frameBuffer->Get().cur.clip != action)
//    {
//        PlayClip((int)action);
//    }
//}


