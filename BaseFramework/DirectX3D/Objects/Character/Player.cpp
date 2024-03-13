#include "Framework.h"

Player::Player() : ModelAnimator("NPC")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");


    CamTransform = new Transform();
    CAM->SetParent(CamTransform);

    frontPoint = new Transform();
    frontPoint->SetParent(this);
    frontPoint->Pos() = { 0,0,-200 };

    Hand = new Transform();
   
    /*
    Gun->Scale() *= 0.8f;
    Gun->Pos().y -= 0.05f;
    Gun->Rot().x += 1.5f;
    Gun->Rot().y -= 0.10f;
    */

    Pos() = { 100, 0, 100 };

    ReadClip("B_Idle");
    ReadClip("B_Walk");
    ReadClip("B_Run");

    ReadClip("J_Start");
    ReadClip("J_End");
    ReadClip("J_Loop");

    ReadClip("R_Idle");
    ReadClip("R_Run");
    ReadClip("R_Aim");
    ReadClip("R_Reload");
    ReadClip("R_Draw");

    ReadClip("RA_Run");

    // ReadClip("B_Mining");

    ReadClip("S_Aim");
    ReadClip("S_Throw");


    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // �׽�Ʈ : �� ��ȹ
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);

    testFrontSphere = new SphereCollider();

    // �׽�Ʈ : ��
    particle = new ParticleSystem("TextData/Particles/Star.fx");

    GetClip(J_START)->SetEvent(bind(&Player::SetState, this, J_LOOP), 0.3f);
    GetClip(J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);

    GetClip(S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.55f);

    GetClip(R_DRAW)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    GetClip(R_RELOAD)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);

    playerCollider = new CapsuleCollider(0.25f,0.7f);
}

Player::~Player()
{
    delete CamTransform;
    delete frontPoint;
    delete testPalSpear;
    delete particle;
    delete playerCollider;
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

    if (!UiManager::Get()->GetUiOn())
    {
        Control();
    }

    SetAnimation();


    //
    playerCollider->Pos() = this->Pos() + Vector3(0,1.0f,0);

    Hand->SetWorld(GetTransformByNode(68));
    
    ModelAnimator::Update();
    PalSpearManager::Get()->Update();

    testFrontSphere->UpdateWorld();

    //
    particle->Update();
    playerCollider->UpdateWorld();
}

void Player::Render()
{
    testPalSpear->Render();
    testFrontSphere->Render();
  
    ModelAnimator::Render();
    PalSpearManager::Get()->Render();

    //
    particle->Render();
    playerCollider->Render();
}

void Player::GUIRender()
{
    //ModelAnimator::GUIRender();
    //PalSpearManager::Get()->GUIRender();
    ImGui::Text("selNum : %d", select);
    ImGui::Text("mouseWheel : %d", mouseWheel);
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

    if (KEY_PRESS(VK_LSHIFT))
    {
        isRun = true;
    }
    else
    {
        isRun = false;
    }

    if (mouseWheel == 1)
    {
        select++;
        //SetState(R_DRAW);
        if (select > 4)
        {
            select = 0;
        }
    }
    else if (mouseWheel == 2)
    {
        select--;
        if (select < 0)
        {
            select = 4;
        }
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
    case 3:
        // other weapon
        isGun = false;
    case 4:
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

        if (KEY_DOWN(VK_LBUTTON)) // 총쏘기
        {
            AttackPal();
        }
        else if (KEY_DOWN('Q')) // 팰 스피어 던지기
        {
            CatchPal();
        }
        //else if (KEY_DOWN('Z')) // 필드 UI에서 소환
        //{
        //    SummonsPal();
        //}
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
    Jump(LandScapeManager::Get()->GetTerrain()->GetHeight(Pos()));
}

void Player::Move()
{
    if (curState == S_THROW)
    {
        return;
    }
    bool isMoveZ = false;
    bool isMoveX = false;




    if (isGaim)
    {

        // CamTransform->Rot().y = Rot().y;

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
            velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //�������� ����

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
    }


}

void Player::Rotate()
{

    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
    CamTransform->Rot().y += delta.x * rotSpeed * DELTA;

    if (isAiming)   Rot().y = CamTransform->Rot().y;


    
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
    // *�ѼҸ� ��� �ʿ�
    //Ray ray;
    //ray.pos = GlobalPos();
    //ray.dir = CamTransform->Forward();
    //Vector3 hitPoint;




    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // �½�Ʈ : ��Ʈ

        // �÷��̾ �� �´� ����Ʈ �� �߰� �ʿ�
        // ����Ʈ�� ��Ʈ ����Ʈ���� ���
        particle->Play(hitPoint);
        

    }


   //  BulletManager::Get()->Throw(Gun->GlobalPos(), ray.dir);

}

void Player::CatchPal()
{
    if (curState == S_THROW)
    {
        return;
    }
    SetState(S_THROW);

    //Ray ray = CAM->ScreenPointToRay(mousePos);

    //Ray ray;
    //ray.pos = CAM->GlobalPos();
    //ray.dir = CAM->Forward();
    //Vector3 hitPoint;

    // �罺�Ǿ� �Ŵ��� �׽�Ʈ
    Vector3 tmpF = CAM->Forward();
    tmpF.y = 0.0f;
    tmpF = tmpF.GetNormalized(); // 앞에서
    Vector3 tmp = CAM->GlobalPos() + CAM->Left() * 0.4f + tmpF * 1.5f + Vector3(0.0f, 1.0f, 0.0f) * 0.2f;
    //tmp.x -= 0.3f;
    //tmp.y += 1.7f;
    //ray.dir += {0, 0.3f, 0};
   // PalSpearManager::Get()->Throw(tmp, ray.dir);
    PalSpearManager::Get()->Throw(tmp, CAM->Forward());

}

void Player::SummonsPal()
{
    // ù��° �� ����
    //PlayerPalsManager::Get()->SetSelPal(0);
    //// �� ��ȯ
    //PlayerPalsManager::Get()->Summons();
}

void Player::UiMode()
{
    UiOn = !UiOn;
}

void Player::SetAnimation()
{
    
    if (curState == S_THROW)
    {
        return;
    }
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
                SetState(R_RUN);

            }
            else SetState(R_IDLE);
            // ���ؽ� ������ �ֱ�
            // ���ؽ� ī�޶��� ȸ���� ���� ȸ���ϱ�


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
