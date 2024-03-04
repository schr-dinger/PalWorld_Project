#include "Framework.h"

Player::Player() : ModelAnimator("NPC")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");

    particle = new ParticleSystem("TextData/Particles/test3.fx");

    CamTransform = new Transform();
    CAM->SetParent(CamTransform);

    frontPoint = new Transform();
    frontPoint->SetParent(this);
    frontPoint->Pos() = { 0,0,-5 };

    Hand = new Transform();
    Gun = new Model("Rifle");
    Gun->SetParent(Hand);

    Gun->Scale() *= 0.8f;
    Gun->Pos().y -= 0.05f;
    Gun->Rot().x += 1.5f;
    Gun->Rot().y -= 0.10f;

    Pos() = { 100, 0, 100 };

    ReadClip("B_Idle");
    ReadClip("B_Walk");
    ReadClip("B_Run");

    ReadClip("J_Start");
    ReadClip("J_End");
    ReadClip("J_DownLoop");

    ReadClip("Rifle_Idle");
    ReadClip("Rifle_Run");
    ReadClip("Rifle_Aim");
    ReadClip("Rifle_Reload");
    ReadClip("Rifle_Draw");


    ReadClip("Rifle_Fwd");
    //ReadClip("Rifle_Back");
    //ReadClip("Rifle_Left");
    //ReadClip("Rifle_Right");

    ReadClip("S_Aim");
    ReadClip("S_Throw");


    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // 테스트 : 팔 포획
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);

    testFrontSphere = new SphereCollider();

    // 테스트 : 총


    GetClip(J_START)->SetEvent(bind(&Player::SetState, this, J_LOOP), 0.3f);
    GetClip(J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);

    GetClip(S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.3f);

    GetClip(R_DRAW)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    GetClip(R_RELOAD)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);


}

Player::~Player()
{
    delete CamTransform;
    delete frontPoint;
    delete Gun;
    delete terrain;
    delete testPalSpear;
    delete particle;
}

void Player::Update()
{

    if (isAiming)
    {
        CAM->Pos() = foCam;
    }
    else
    {
        CAM->Pos() = ogCam;
    }

    CamTransform->Pos() = this->Pos();

    testFrontSphere->Pos() = frontPoint->GlobalPos();

    //ClipSync();
    CamTransform->UpdateWorld();
    frontPoint->UpdateWorld();
    Control();
    SetAnimation();

    if(isGun) Hand->SetWorld(GetTransformByNode(68));
    else Hand->SetWorld(GetTransformByNode(4));
    
    Gun->UpdateWorld();

    particle->Update();

    ModelAnimator::Update();
    PalSpearManager::Get()->Update();

    testFrontSphere->UpdateWorld();
}

void Player::Render()
{
    testPalSpear->Render();
    //testFrontSphere->Render();
    Gun->Render();

    particle->Render();
    ModelAnimator::Render();
    PalSpearManager::Get()->Render();

}

void Player::GUIRender()
{
    ModelAnimator::GUIRender();
    //PalSpearManager::Get()->GUIRender();

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

    // 테스트 : 팔 포획, 팔을 맞췄을 때만 팔스피어 콜라이더 활성화
    testPalSpear->SetActive(false);

    if (KEY_PRESS(VK_LSHIFT))
    {
        isRun = true;
    }
    else
    {
        isRun = false;
    }

    if (KEY_DOWN('1'))
    {
        select = 1;
        SetState(R_DRAW);
    }

    if (KEY_DOWN('2'))
    {
        select = 2;
    }

    switch (select)
    {
    case 1:
        isGun = true;
        if (KEY_DOWN('R'))
        {
            SetState(R_RELOAD);
        }
        // other weapon
        break;
    case 2:
        // other weapon
        isGun = false;
    default:
        isGun = false;
        //othere weapon
        break;

    }


    if (KEY_PRESS(VK_RBUTTON))
    {
        isAiming = true;

        switch (select)
        {
        case 1:
            isGaim = true;
            break;
        case 2:
            //  isSpearAiming = true;
            break;
        default:
            break;
        }





        if (KEY_DOWN(VK_LBUTTON)) // 팔 공격
        {
            AttackPal();
        }
        else if (KEY_DOWN('V')) // 팔 포획
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
        isAiming = false;
        isGaim = false;

    }

    if (KEY_DOWN('R'))
    {
        test = !test;
    }



    if (test)
    {
        Rotate();
    }


    Jump(terrain->GetHeight(Pos()));
}

void Player::Move()
{
    bool isMoveZ = false;
    bool isMoveX = false;




    if (isGaim)
    {


        CamTransform->Rot().y = Rot().y;

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



        if (velocity.Length() > 1) velocity.Normalize();



        if (!isMoveZ)
            velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간으로 감속

        if (!isMoveX)
            velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

        Matrix rotY = XMMatrixRotationY(Rot().y);
        Vector3 direction = XMVector3TransformCoord(velocity, rotY);
        //direction.y;


        Pos() += direction * moveSpeed * DELTA * -1;
    }
    else
    {

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
            action = J_START;
            jumpVelocity = jumpForce;
            isJump = true;
            isSpace = true;
        }

        velocity = w + a + s + d;
        velocity.Normalize();

        //여기서부터 다시보기
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
    }


}

void Player::Rotate()
{

    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    //SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    //if (isGaim) Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x = -delta.y * rotSpeed*0.005f;
    CamTransform->Rot().y = delta.x * rotSpeed* 0.005f;

    if (isAiming)     Rot().y = CamTransform->Rot().y;


}

void Player::Jump(float _ground)
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > _ground + 0.5f)
    {
        if (action != J_LOOP) action = J_LOOP;

        isJump = true;
    }
    else if (Pos().y < _ground)
    {

        //Pos().y = _ground;
        Pos().y = Lerp(Pos().y, _ground, 10 * DELTA);
        jumpVelocity = 0;
        if (curState == J_LOOP) SetState(J_END);
        isJump = false;
        isSpace = false;
    }

}

void Player::AttackPal()
{
    // *총소리 출력 필요
    //Ray ray;
    //ray.pos = GlobalPos();
    //ray.dir = CamTransform->Forward();
    //Vector3 hitPoint;




    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // 태스트 : 히트

        // 플레이어에 총 맞는 이펙트 등 추가 필요

        // 이펙트는 히트 포인트에서 출력
    }


    BulletManager::Get()->Throw(Gun->GlobalPos(), ray.dir);




}

void Player::CatchPal()
{
    //Ray ray = CAM->ScreenPointToRay(mousePos);

    Ray ray;
    ray.pos = CAM->GlobalPos();
    ray.dir = CAM->Forward();
    Vector3 hitPoint;

    // 펠스피어 매니저 테스트
    Vector3 tmp = this->GlobalPos();
    tmp.y += 2;
    ray.dir += {0, 0.3f, 0};
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
    //Ray ray = CAM->ScreenPointToRay(mousePos);
    //Vector3 hitPoint;

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


    if (curState == J_LOOP)
    {
        ClipOnce();
        return;
    }

    if (isGun)
    {


        if (isGaim)
        {

            if (velocity.Length() > 0)
            {
                SetState(RA_FWD);
            }
            else SetState(R_Aim);


        }
        else
        {



            if (velocity.Length() > 0)
            {
                SetState(RUN);

            }
            else SetState(IDLE);
            // 조준시 움직임 넣기
            // 조준시 카메라의 회전을 따라서 회전하기


        }


        return;
    }






    if (isJump)
    {
        SetState(J_START);
    }
    else
    {
        if (velocity.Length() > 0)
        {
            if (isRun) SetState(RUN);
            else SetState(WALK);

        }
        else
        {
            SetState(IDLE);
        }
    }

}

void Player::SetState(ACTION state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);

}
