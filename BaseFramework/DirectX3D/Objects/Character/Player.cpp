#include "Framework.h"

Player::Player() :	ModelAnimator("Player")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);


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
}

Player::~Player()
{
}

void Player::Update()
{
    //ClipSync();
    Control();
    SetAnimation();
    ModelAnimator::Update();
}

void Player::Render()
{
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
    if (KEY_PRESS('V'))
    {
        Rotate();
    }
    //Jump();
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

void Player::Rotate()
{
     Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
     SetCursorPos(clientCenterPos.x, clientCenterPos.y);
     Rot().y += delta.x * rotSpeed * DELTA;
     CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Player::Jump(float _ground)
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > _ground && isSpace)
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;
        isJump = true;
    }

    if (Pos().y < _ground)
    {
        Pos().y = _ground;
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
        isSpace = false;
    }

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
