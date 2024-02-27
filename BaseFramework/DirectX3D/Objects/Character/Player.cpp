#include "Framework.h"

Player::Player() :	ModelAnimator("Player")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");


    CamTransform = new Transform();
    CAM->SetParent(CamTransform);
    CAM->Pos() = { -0.05,2.5,2.5 };

    Pos() = { 100, 0, 100 };
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

    // �׽�Ʈ : �� ��ȹ
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
    PalSpearManager::Get()->Update();

}

void Player::Render()
{
    testPalSpear->Render();

    ModelAnimator::Render();
    PalSpearManager::Get()->Render();

}

void Player::GUIRender()
{
    ModelAnimator::GUIRender();
    PalSpearManager::Get()->GUIRender();

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

    // �׽�Ʈ : �� ��ȹ, ���� ������ ���� �Ƚ��Ǿ� �ݶ��̴� Ȱ��ȭ
    testPalSpear->SetActive(false);

    if (KEY_PRESS('V'))
    {
        isAiming = true;

        if (KEY_DOWN(VK_LBUTTON)) // �� ����
        {
            AttackPal();
        }
        else if (KEY_DOWN(VK_RBUTTON)) // �� ��ȹ
        {
            CatchPal();
        }
        else if (KEY_DOWN('Z')) // ��ȹ�� �� ��ȯ
        {
            SummonsPal();
        }
    }
    else
    {
        isAiming = false;

    }

    Rotate();

    Jump(terrain->GetHeight(Pos()));
}

void Player::Move()
{
    bool isMoveZ = false;
    bool isMoveX = false;

    if (KEY_PRESS('W'))
    {
        w = -CamTransform->Forward();
        isMoveZ = true;
    }
    else
    {
        w = z;
    }

    if (KEY_PRESS('S'))
    {
        s = -CamTransform->Back();
        isMoveZ = true;
    }
    else
    {
        s = z;
    }


    if (KEY_PRESS('A'))
    {
        a = -CamTransform->Left();
        isMoveX = true;
    }
    else
    {
        a = z;
    }


    if (KEY_PRESS('D'))
    {
        d = -CamTransform->Right();
        isMoveX = true;
    }
    else
    {
        d = z;
    }

    if (KEY_DOWN(VK_SPACE))
    {
        action = ACTION::JUMP;
        jumpVelocity = jumpForce;
        isJump = true;
        isSpace = true;
    }

    velocity = w + a + s + d;
    velocity.Normalize();
    
    //���⼭���� �ٽú���
    Vector3 forward = Forward();
    Vector3 cross = Cross(forward, velocity);

    if (cross.y < 0)
    {
        Rot().y += 5 * DELTA;
    }
    else if (cross.y > 0)
    {
        Rot().y -= 5 * DELTA;
    }


    Pos() += velocity * moveSpeed * DELTA;
    //if (KEY_PRESS('W'))
    //{
    //    velocity += CamTransform->Forward() * DELTA;

    //    isMoveZ = true;
    //}

    //if (KEY_PRESS('S'))
    //{
    //    velocity += CamTransform->Back() * DELTA;
    //    isMoveZ = true;
    //}

    //if (KEY_PRESS('A'))
    //{
    //    velocity += CamTransform->Left() * DELTA;
    //    isMoveX = true;
    //}

    //if (KEY_PRESS('D'))
    //{
    //    velocity += CamTransform->Right() * DELTA;
    //    isMoveX = true;
    //}


    //if (KEY_DOWN(VK_SPACE))
    //{
    //    action = ACTION::JUMP;
    //    jumpVelocity = jumpForce;
    //    isJump = true;
    //    isSpace = true;
    //}

    //if (velocity.Length() > 1) velocity.Normalize();



    //if (!isMoveZ)
    //    velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //�������� ����

    //if (!isMoveX)
    //    velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    //Matrix rotY = XMMatrixRotationY(Rot().y);
    //Vector3 direction = XMVector3TransformCoord(velocity, rotY);
    //Rot().y = direction.y;

    //Pos() += direction * moveSpeed * DELTA*-1;

}

void Player::Rotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    CamTransform->Rot().y += delta.x * rotSpeed * DELTA;

    if(isAiming)     Rot().y = CamTransform->Rot().y;


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
    // *�ѼҸ� ��� �ʿ�

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // �½�Ʈ : ��Ʈ
        
        // �÷��̾ �� �´� ����Ʈ �� �߰� �ʿ�

        // ����Ʈ�� ��Ʈ ����Ʈ���� ���
    }
   
}

void Player::CatchPal()
{
    //Ray ray = CAM->ScreenPointToRay(mousePos);
    Ray ray;
    ray.pos = CAM->GlobalPos();
    ray.dir = CAM->Forward();
    Vector3 hitPoint;

    // �罺�Ǿ� �Ŵ��� �׽�Ʈ
    Vector3 tmp = this->GlobalPos();
    tmp.y += 2;
    PalSpearManager::Get()->Throw(tmp, ray.dir);

    //if (PalsManager::Get()->IsCollision(ray, hitPoint))
    //{
    //    PalSpearManager::Get()->Throw(tmp, ray.dir);
    //}
    
    //PalSpearManager::Get()->Throw(tmp, this->Back());
    //PalSpearManager::Get()->Throw(this->GlobalPos(), this->Back());
    
    //if (PalsManager::Get()->IsCollision(ray, hitPoint))
    //{
    //    testPalSpear->SetActive(true);
    //    testPalSpear->Pos() = hitPoint;
    //    testPalSpear->UpdateWorld();
    //}

}

void Player::SummonsPal()
{
    // ù��° �� ����
    PlayerPalsManager::Get()->SetSelPal(0);
    // �� ��ȯ
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
