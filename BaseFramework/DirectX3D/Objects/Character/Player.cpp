#include "Framework.h"

Player::Player() :	ModelAnimator("Player")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");


    CamTransform = new Transform();
    CAM->SetParent(CamTransform);
    CAM->Pos() = { 10,5,10 };

    Pos() = { -5, 10, 5 };
    ReadClip("Idle");

    ReadClip("WalkF");
    ReadClip("WalkR");
    ReadClip("WalkL");

    ReadClip("RunF");
    ReadClip("RunR");
    ReadClip("RunL");

    ReadClip("Jump");

    ReadClip("Attack");

    ReadClip("Damage");

    ReadClip("Draw");
    ReadClip("Aim");
    ReadClip("Shoot");


    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // 테스트 : 팔 포획
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);
}

Player::~Player()
{
    delete CamTransform;
}

void Player::Update()
{
    CamTransform->Pos() = this->Pos();

    //ClipSync();
    CamTransform->UpdateWorld();
    Control();
    SetAnimation();
    ModelAnimator::Update();
}

void Player::Render()
{
    testPalSpear->Render();

    ModelAnimator::Render();
}

void Player::GUIRender()
{
    ModelAnimator::GUIRender();
}

void Player::ClipSync()
{
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        PlayClip((int)action);
    }
}

void Player::Control()
{
    Move();

    //if (KEY_PRESS(VK_LEFT))
    //{
    //    Rot().y += DELTA;
    //}

    //if (KEY_PRESS(VK_RIGHT))
    //{
    //    Rot().y -= DELTA;
    //}

    // 테스트 : 팔 포획, 팔을 맞췄을 때만 팔스피어 콜라이더 활성화
    testPalSpear->SetActive(false);

    if (KEY_PRESS('V'))
    {
        AimRotate();
        if (KEY_DOWN(VK_LBUTTON)) // 팔 공격
        {
            AttackPal();
        }
        else if (KEY_DOWN(VK_RBUTTON)) // 팔 포획
        {
            CatchPal();
        }
        else if (KEY_DOWN('Z')) // 포획한 팔 소환
        {
            SummonsPal();
        }
    }
    else
    {
        Rotate();
    }
   
    Jump(terrain->GetHeight(Pos()));
}

void Player::Move()
{
    bool isMoveZ = false;
    bool isMoveX = false;

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA;
        isMoveZ = true;
    }

    if (KEY_PRESS('S'))
    {
        velocity.z -= DELTA;
        isMoveZ = true;
    }

    if (KEY_PRESS('A'))
    {
        velocity.x -= DELTA;
        isMoveX = true;
    }

    if (KEY_PRESS('D'))
    {
        velocity.x += DELTA;
        isMoveX = true;
    }

    if (KEY_DOWN(VK_SPACE))
    {
        action = ACTION::JUMP;
        jumpVelocity = jumpForce;
        isJump = true;
        isSpace = true;
    }


    if (velocity.Length() > 1) velocity.Normalize();

    if (!isMoveZ)
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간으로 감속

    if (!isMoveX)
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    Matrix rotY = XMMatrixRotationY(Rot().y);
    Vector3 direction = XMVector3TransformCoord(velocity, rotY);

    Pos() += direction * moveSpeed * DELTA*-1;

}

void Player::AimRotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Player::Rotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    CamTransform->Rot().y += delta.x * rotSpeed * DELTA;

}

void Player::Jump(float _ground)
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > _ground+0.5f )
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;

        isJump = true;
    }

    if (Pos().y < _ground )
    {

        //Pos().y = _ground;
        Pos().y = Lerp(Pos().y, _ground, 10*DELTA);
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
        isSpace = false;
    }

}

void Player::AttackPal()
{
    // *총소리 출력 필요

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // 태스트 : 히트
        
        // 플레이어에 총 맞는 이펙트 등 추가 필요

        // 이펙트는 히트 포인트에서 출력
    }
   
}

void Player::CatchPal()
{
    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        testPalSpear->SetActive(true);
        testPalSpear->Pos() = hitPoint;
        testPalSpear->UpdateWorld();
    }

}

void Player::SummonsPal()
{
    // 첫번째 팔 선택
    PlayerPalsManager::Get()->SetSelPal(0);
    // 팔 소환
    PlayerPalsManager::Get()->Summons();
}

void Player::SetAnimation()
{
    if (curState == ACTION::SHOOT) return;

    if (isJump)
    {
        SetState(ACTION::JUMP);
    }
    else
    {
        if (velocity.z > 0.1f)
            SetState(ACTION::RUNF);
        else if (velocity.z < -0.1f)
            SetState(ACTION::RUNF);
        else if (velocity.x > 0.1f)
            SetState(ACTION::RUNR);
        else if (velocity.x < -0.1f)
            SetState(ACTION::RUNL);
        else SetState(ACTION::IDLE);
    }

}

void Player::SetState(ACTION state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);

}
