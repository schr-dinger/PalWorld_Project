#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.01f, 0.01f, 0.01f }; // 크기 기본값은 1
                                      // 나중에 크기가 바뀌어야 하면 와서 수정하게
    transform->Rot().x = XM_PIDIV2;

    terrain = nullptr;
    pal = nullptr;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //크기 기본값은 1.0
    collider->Pos() = {};            //위치 기본값 : 부모 위치

    state = State::THROW;

    // StateHitPal용
    hitPalTime = 0.0f;

    // StateCatching용
    catchingTime = 0.0f;
    shakeNum = 0;
    shakeTime = 0;
}

PalSpear::~PalSpear()
{
    delete collider;

}

void PalSpear::Update()
{
    //비활성화 중에는 안 움직임
    if (!transform->Active()) return;

    switch (state)
    {
    case PalSpear::State::THROW:
        StateThrow();
        break;
    case PalSpear::State::HITPAL:
        StateHitPal();
        break;
    case PalSpear::State::CATCHING:
        StateCatching();
        break;
    case PalSpear::State::SUCCESS:
        StateSuccess();
        break;
    case PalSpear::State::FAIL:
        StateFail();
        break;
    default:
        break;
    }

    collider->UpdateWorld();
}

void PalSpear::Render()
{
    if (!transform->Active()) return;
    collider->Render();
}

void PalSpear::GUIRender()
{
    if (!transform->Active()) return;
    ImGui::Text("Down : %f", downForce);
}

void PalSpear::Throw(Vector3 pos, Vector3 dir)
{
    //활성화
    transform->SetActive(true);
    collider->SetActive(true);
    transform->Pos() = pos;
    direction = dir;

    //방향에 맞게 모델(=트랜스폼) 회전 적용
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2; //방향 적용 + 모델 정면에 따른 보정
                                                          //쿠나이 모델은 90도 돌아가 있었음
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           ↑ 각도를 호도로 바꿔주는 함수

    time = 0; //경과시간 리셋
}

void PalSpear::StateThrow()
{
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    transform->Pos() += direction * speed * DELTA;
    transform->Pos() += tmp * DELTA;
    speed -= DELTA * 3;
    if (speed <= 0.0f)
    {
        speed = 0.0f;
        if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
        {
            transform->Pos().y = terrain->GetHeight(transform->GlobalPos());
            time += DELTA; // 시간 경과에 따라 변수에 누적
            if (time > LIFE_SPAN)
            {
                transform->SetActive(false);
                speed = 15.0f;
                downForce = 0.0f;
            }
        }
    }
    if (transform->Pos().y < terrain->GetHeight(transform->GlobalPos()))
    {
        Vector3 normal;
        transform->Pos().y = terrain->GetHeight(transform->GlobalPos(), &normal);
        normal *= -1;
        Vector3 tmpDir = (direction + tmp) * -1;
        //tmpDir = tmpDir.GetNormalized();
        Vector3 tmpD = 2 * normal * (Dot(tmpDir, normal));
        tmpDir *= -1;
        direction = (tmpDir + tmpD).GetNormalized();
        downForce = 0.0f;
        speed *= 0.7;
    }
}

void PalSpear::StateHitPal()
{
    hitPalTime += DELTA;
    transform->Pos() += Vector3(0.0f, 1.0f, 0.0f) * 2 * DELTA;  // 위로
    transform->Pos() += transform->Left() * DELTA; // 던지는 방향 반대
    transform->Pos() += transform->Down() * 2 * DELTA; // 오른쪽
    if (hitPalTime > 0.4f)
    {
        state = State::CATCHING;
        hitPalTime = 0.0f;
    }
}

void PalSpear::StateCatching()
{
    catchingTime += DELTA;
    if (catchingTime > 0.5f)
    {
        transform->Rot().x = XM_PIDIV2;
        transform->Rot().y = 0;
        transform->Rot().z = 0;
        if (catchingTime > 1.0f)
        {
            catchingTime = 0.0f;
            shakeNum++;

            if (shakeNum == 4)
            {
                shakeNum == 0;
                transform->SetActive(false);
                if (RANDOM->Int(0,1) == 0)
                {
                    state = State::SUCCESS;
                }
                else
                {
                    state = State::FAIL;
                }
            }
        }
        
    }
    else
    {
        float tmpRX = RANDOM->Float(-45.0f, 45.0f);
        float tmpRY = RANDOM->Float(-45.0f, 45.0f);
        float tmpRZ = RANDOM->Float(-45.0f, 45.0f);
        tmpRX = XM_PIDIV2 + XMConvertToRadians(tmpRX);
        tmpRY = XMConvertToRadians(tmpRY);
        tmpRZ = XMConvertToRadians(tmpRZ);
        transform->Rot().x = Lerp(transform->Rot().x, tmpRX, 0.5f);
        transform->Rot().y = Lerp(transform->Rot().x, tmpRY, 0.5f);
        transform->Rot().z = Lerp(transform->Rot().x, tmpRZ, 0.5f);
    }
    
    
}

void PalSpear::StateSuccess()
{
}

void PalSpear::StateFail()
{
}
