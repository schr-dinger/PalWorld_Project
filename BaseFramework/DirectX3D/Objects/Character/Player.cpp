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
    //ReadClip("B_Run");
    //
    //ReadClip("J_Start");
    //ReadClip("J_End");
    //ReadClip("J_Loop");
    //
    //ReadClip("R_Idle");
    //ReadClip("R_Run");
    //ReadClip("R_Aim");
    //ReadClip("R_Reload");
    //ReadClip("R_Draw");
    //
    //ReadClip("RA_Run");
    //
    //ReadClip("BW_Aim");
    //ReadClip("BW_Fire");
    //
    ReadClip("M_Mining");
    //ReadClip("M_Attack");
    //
    //ReadClip("S_Aim");
    //ReadClip("S_Throw");

    //ReadClip("BW_Run");
    //ReadClip("BW_A_Ready");


    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // 테스트 포획
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);

    testFrontSphere = new SphereCollider();

    summonPalSpear = new Model("PalSpear");
    summonPalSpear->Scale() = { 0.02f, 0.02f, 0.02f };
    summonPalSpear->Pos() = {-0.05f, 0.05f, -0.12f};
    summonPalSpear->Rot().x = XM_PIDIV2;
    summonPalSpear->SetParent(Hand);
    summonPalSpear->SetActive(false);
    summonPalSpearThrow = new Model("PalSpear");
    summonPalSpearThrow->Scale() = { 0.02f, 0.02f, 0.02f };
    //summonPalSpearThrow->Pos() = { -0.05f, 0.05f, -0.12f };
    summonPalSpearThrow->Rot().x = XM_PIDIV2;
    summonPalSpearThrow->SetActive(false);
    summonPalSpearCollider = new SphereCollider();
    summonPalSpearCollider->SetParent(summonPalSpear);
    summonPalSpearCollider->Scale() = { 7, 7, 7 }; //크기 기본값은 1.0
    summonPalSpearCollider->Pos() = {};            //위치 기본값 : 부모 위치
    summonPalSpearDIr = {};

    // �׽�Ʈ : ��
    particle = new ParticleSystem("TextData/Particles/test2.fx");

    //GetClip(J_START)->SetEvent(bind(&Player::SetState, this, J_LOOP), 0.3f);
    //GetClip(J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    //
    //GetClip(S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.55f);
    //
    //GetClip(R_DRAW)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    //GetClip(R_RELOAD)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    //
    //GetClip(BW_FIRE)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    //GetClip(M_ATTACK)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    GetClip(M_MINING)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);
    // GetClip(M_MINING)->SetEvent(bind(&Player::MState, this), 0.7f);

    playerCollider = new CapsuleCollider(0.25f,0.7f);
    MiningCollider = new SphereCollider(0.2f);
    MiningCollider->SetActive(false);
       
    

    weapons.resize(4);
}

Player::~Player()
{
    delete CamTransform;
    delete frontPoint;
    delete testPalSpear;
    delete particle;
    delete playerCollider;
    delete summonPalSpear;
    delete summonPalSpearCollider;
    delete MiningCollider;

    weapons.clear();
}

void Player::Update()
{

    if (isAiming)
    {
        //CAM->Pos() = foCam;
        CAM->Pos() = Lerp(ogCam, foCam, 0.8f);
    }
    else
    {
        //CAM->Pos() = ogCam;
        CAM->Pos() = Lerp(foCam, ogCam, 0.8f);


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

    if (weapons[0] != nullptr)
    {
        MiningCollider->SetParent(weapons[0]->GetParent());
        MiningCollider->Pos() = Vector3(0.0f, 0.3f, 0.0f);
    }
    
    //
    playerCollider->Pos() = this->Pos() + Vector3(0,1.0f,0);
    

    Hand->SetWorld(GetTransformByNode(68));
    FOR(weapons.size())
    {
        if (weapons[i] != nullptr)
        {
            weapons[i]->SetParent(Hand);
            weapons[i]->UpdateWorld();
        }


    }


    ModelAnimator::Update();
    PalSpearManager::Get()->Update();

    testFrontSphere->UpdateWorld();

    
    playerCollider->UpdateWorld();
    if(MiningCollider->Active()) MiningCollider->UpdateWorld();

    // 팰 스피어 던지기 관련
    ThrowPalSpear();
    summonPalSpear->UpdateWorld();
    summonPalSpearThrow->UpdateWorld();
    summonPalSpearCollider->UpdateWorld();
}

void Player::Render()
{
    testPalSpear->Render();
    testFrontSphere->Render();
  
    ModelAnimator::Render();
    PalSpearManager::Get()->Render();

    //
    
    playerCollider->Render();

    summonPalSpear->Render();
    summonPalSpearThrow->Render();
    summonPalSpearCollider->Render();

    //
    FOR(weapons.size())
    {
        if (weapons[select - 1] != nullptr)  weapons[select - 1]->Render();

    }
    if (MiningCollider->Active()) MiningCollider->Render();


}

void Player::ShadowRender()
{
    ModelAnimator::SetShader(L"Light/DepthMap.hlsl");
    ModelAnimator::Render();
    ModelAnimator::SetShader(L"Model/ModelAnimation.hlsl");

}

void Player::GUIRender()
{
    //ModelAnimator::GUIRender();
    //PalSpearManager::Get()->GUIRender();
    //ImGui::Text("selNum : %d", curState);
    //ImGui::Text("mouseWheel : %d", mouseWheel);

    MiningCollider->GUIRender();


    ImGui::Text("CAM 1 : %2.f", CamTransform->Pos().y);
    ImGui::Text("Pos 1 : %2.f", Pos().y);


    ImGui::Text("velocity 1 : %3.f", velocity.x);
    ImGui::Text("velocity 2 : %3.f", velocity.z);

    ImGui::Text("cross : %3.f", testyo.y);
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
        mouseWheel = 0;
        select++;
        //SetState(R_DRAW);
        if (select > 4)
        {
            select = 1;
        }
    }
    else if (mouseWheel == 2)
    {
        mouseWheel = 0;

        select--;
        if (select < 1)
        {
            select = 3;
        }
    }
    
    if (ItemManager::Get()->GetEquipV()[select - 1] != nullptr)
    {
        switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
        {
        case 1:
            isGun = true;
            isBow = false;
            if (KEY_DOWN('R'))
            {
                //SetState(R_RELOAD);
            }

            break;
        case 2:
            isBow = true;
            isGun = false;
            break;
        case 3:
            // mining or spear
            isGun = false;
            isBow = false;
            break;
        default:
            isGun = false;
            isBow = false;
            //othere weapon
            break;

        }

    }
    else
    {
        isGun = false;
        isBow = false;

    }


    if (KEY_PRESS(VK_RBUTTON))
    {
        isAiming = true;


        if (ItemManager::Get()->GetEquipV()[select - 1] != nullptr)
        {
            W_Aiming = true;

            switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
            {
            case 1:
                isGaim = true;
              
                break;
            case 2:
                isBaim = true;
                break;
            case 3:
                //  isSpearAiming = true;
                break;
            default:
                isGaim = false;
                isBaim = false;
                break;
            }
            if (KEY_DOWN(VK_LBUTTON)) // �� ����
            {
                AttackPal();
            }
        }
    }
    else if (KEY_UP(VK_RBUTTON))
    {
        isAiming = false;
        W_Aiming = false;
        isGaim = false;
        isBaim = false;
    }
    else if (KEY_PRESS('Q') || KEY_PRESS('E'))
    {
        //if (curState != S_THROW)
        //{
        //    SetState(ACTION::S_AIM);
            isAiming = true;
            summonPalSpear->SetActive(true);
        //}
    }
    else if (KEY_UP('Q'))
    {
        //if (curState == S_AIM)
        //{
            CatchPal();
            isAiming = false;
            summonPalSpear->SetActive(false);
        //}
    }
    else if (KEY_UP('E'))
    {
        //if (curState == S_AIM)
        //{
            SummonsPal();
            isAiming = false;
            summonPalSpear->SetActive(false);
            summonPalSpearThrow->SetActive(true);
            summonPalSpearThrow->Pos() = summonPalSpear->GlobalPos();
            summonPalSpearDIr = CAM->Forward();
        //}

    }
           
    if (KEY_DOWN('G'))
    {
        MiningCollider->SetActive(true);
        SetState(M_MINING);
    }

    if (KEY_DOWN('N'))
    {
        MiningCollider->SetActive(false);
        
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
    //if (curState == S_THROW)
    //{
    //    return;
    //}
    bool isMoveZ = false;
    bool isMoveX = false;


    if (W_Aiming)
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
            //action = J_START;
            jumpVelocity = jumpForce;
            isJump = true;
            isSpace = true;
        }

        velocity = w + a + s + d;
        velocity.Normalize();

        //���⼭���� �ٽú���
        Vector3 forward = Forward();
        Vector3 cross = Cross(forward, velocity);
               

        if (cross.y < -0.2f)
        {
            Rot().y += 5.0f * DELTA;
        }
        else if (cross.y > 0.2f)
        {
            Rot().y -= 5.0f * DELTA;
        }


        if (cross.y < -0.1f)
        {
            Rot().y += 3.0f * DELTA;

        }
        else if (cross.y > 0.1f)
        {
            Rot().y -= 3.0f * DELTA;
        }


        // Lerp(Rot().y, CamTransform->Rot().y, 0.5f);
                

        //Rot().y = Lerp(Rot().y, atan2(velocity.x, velocity.z), XM_PIDIV4);


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
        //if (action != J_LOOP) action = J_LOOP;

        isJump = true;
    }
    else if (Pos().y < _ground)
    {

        //Pos().y = _ground;
        Pos().y = Lerp(Pos().y, _ground, 10 * DELTA);
        jumpVelocity = 0;
        //if (curState == J_LOOP) SetState(J_END);
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

    switch (ItemManager::Get()->GetEquipV()[select - 1]->num)
    {
    case 1:

        break;
    case 2:
        //SetState(BW_FIRE);
        break;
    case 3:
        //SetState(M_ATTACK);

        break;
    default:

        break;
    }

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // �½�Ʈ : ��Ʈr

        // �÷��̾ �� �´� ����Ʈ �� �߰� �ʿ�
        // ����Ʈ�� ��Ʈ ����Ʈ���� ���
        particle->Play(hitPoint);
        

    }


   //  BulletManager::Get()->Throw(Gun->GlobalPos(), ray.dir);

}

void Player::CatchPal()
{
    //if (curState == S_THROW)
    //{
    //    return;
    //}
    //SetState(S_THROW);

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
    PalSpearManager::Get()->Throw(summonPalSpear->GlobalPos(), CAM->Forward());

}

void Player::SummonsPal()
{
    //SetState(ACTION::S_THROW);
}

void Player::ThrowPalSpear()
{
    if (!summonPalSpearThrow->Active()) return;
    downForce += gravi * DELTA;

    Vector3 tmp = (down * downForce);

    summonPalSpearThrow->Pos() += summonPalSpearDIr * speed * DELTA;
    summonPalSpearThrow->Pos() += tmp * DELTA;
    if (summonPalSpearThrow->Pos().y < LandScapeManager::Get()->GetTerrain()->GetHeight(summonPalSpearThrow->GlobalPos()))
    {
        summonPalSpearThrow->Pos().y = LandScapeManager::Get()->GetTerrain()->GetHeight(summonPalSpearThrow->GlobalPos());
        downForce = 0.0f;
        speed = 20.0f;
        summonPalSpearThrow->SetActive(false);
        PlayerPalsManager::Get()->Summons(summonPalSpearThrow->GlobalPos());
    }
}

void Player::UiMode()
{
    UiOn = !UiOn;
}

void Player::SetAnimation()
{
    /*
    if (curState == J_LOOP)
    {
        ClipOnce();
        return;
    }
    else if (curState == S_THROW || curState == S_AIM || curState == R_RELOAD || curState == BW_FIRE || curState == M_ATTACK || curState == M_MINING)
    {
        return;
    }

    if (isBow)
    {
        if (isBaim) SetState(BW_AIM);
        else
        {
            if (velocity.Length() > 0) SetState(RUN);
            else  SetState(IDLE);
        }

        return;
    }
    else if (isGun)
    {
        if (isGaim)
        {
            if (velocity.Length() > 0) SetState(RA_FWD);
            else SetState(R_Aim);
        }
        else
        {
            if (velocity.Length() > 0) SetState(R_RUN);
            else SetState(R_IDLE);
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
    */
}

void Player::SetState(ACTION state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);

}
