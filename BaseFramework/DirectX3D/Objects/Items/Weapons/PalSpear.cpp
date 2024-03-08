#include "Framework.h"

PalSpear::PalSpear(Transform* transform) : transform(transform)
{
    transform->Scale() = { 0.01f, 0.01f, 0.01f }; // 크기 기본값은 1
                                      // 나중에 크기가 바뀌어야 하면 와서 수정하게
    transform->Rot().x += XM_PIDIV2;

    terrain = nullptr;
    pal = nullptr;

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 7, 7, 7 }; //크기 기본값은 1.0
    collider->Pos() = {};            //위치 기본값 : 부모 위치

    state = State::THROW;
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
    collider->Render();
}

void PalSpear::GUIRender()
{
    ImGui::Text("Down : %f", downForce);
}

void PalSpear::Throw(Vector3 pos, Vector3 dir)
{
    //활성화
    transform->SetActive(true);

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
    transform->Pos() += Vector3(0.0f, 1.0f, 0.0f) * 2 * DELTA;
    transform->Pos() += transform->Right() * 2 * DELTA;
    transform->Pos() += transform->Back() * 2 * DELTA;

}

void PalSpear::StateCatching()
{
}

void PalSpear::StateSuccess()
{
}

void PalSpear::StateFail()
{
}
