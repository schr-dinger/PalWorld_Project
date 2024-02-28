#include "Framework.h"

Player::Player() :	ModelAnimator("NPC")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    //CAM->SetTarget(this);
    //CAM->TargetOptionLoad("test3");

    
    CamTransform = new Transform();
    CAM->SetParent(CamTransform);
    CAM->Pos() = { -0.05,5,2.5 };
        
    Pos() = { 100, 0, 100 };

    ReadClip("B_Idle");
    ReadClip("B_Walk");
    ReadClip("B_Run");
    
    ReadClip("J_Start");
    ReadClip("J_End");
    ReadClip("J_DownLoop");
   
    ReadClip("Rifle_idle");
    ReadClip("Rifle_run");
    ReadClip("Rifle_Aim");
    ReadClip("Rifle_reload");
    ReadClip("Rifle_draw");

       
    ReadClip("Rifle_Fwd");
    ReadClip("Rifle_Back");
    ReadClip("Rifle_Left");
    ReadClip("Rifle_Right");
    
    ReadClip("S_Aim");
    ReadClip("S_Throw");
    

    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // �׽�Ʈ : �� ��ȹ
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);


    //

    GetClip(J_START)->SetEvent(bind(&Player::SetState, this, J_LOOP),0.3f);
    GetClip(J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.7f);

    GetClip(S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.3f);

    GetClip(R_DRAW)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);
    GetClip(R_RELOAD)->SetEvent(bind(&Player::SetState, this, R_IDLE), 0.3f);


}

Player::~Player()
{
    delete CamTransform;
    delete CamTransform;
    delete Gun;
    delete terrain;
    delete testPalSpear;
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
            // isThorw = true;

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

    if (KEY_DOWN('1'))
    {
        isGun = true;
        select = 1;
    }

    if (KEY_DOWN('2'))
    {
        isGun = false;
        select = 2;
    }



    if (KEY_PRESS(VK_RBUTTON))
    {
        if (isGun)
        {
            isGaim = true;
        }


    }

    if (KEY_DOWN('R'))
    {
        if(isGun)
        SetState(R_RELOAD);
    }







    if (select == 1)
    {
        if(KEY_PRESS(VK_RBUTTON))
        {
             isGaim = true;
        }
        else
        {
            isGaim = false;
        }

        if (KEY_DOWN('R'))
        {
            SetState(R_RELOAD);
        }
    }



    Rotate();

    Jump(terrain->GetHeight(Pos()));
}

void Player::Move()
{
    
    /*
    if (isGaim)
    {
        bool isMoveZ2 = false;
        bool isMoveX2 = false;

      

        Pos() += velocity * moveSpeed * DELTA;

        if (KEY_PRESS('W'))
        {
            velocity += CamTransform->Forward() * DELTA;

            isMoveZ2 = true;
        }

        if (KEY_PRESS('S'))
        {
            velocity += CamTransform->Back() * DELTA;
            isMoveZ2 = true;
        }

        if (KEY_PRESS('A'))
        {
            velocity += CamTransform->Left() * DELTA;
            isMoveX2 = true;
        }

        if (KEY_PRESS('D'))
        {
            velocity += CamTransform->Right() * DELTA;
            isMoveX2 = true;
        }



        if (velocity.Length() > 1) velocity.Normalize();


        if (!isMoveZ2)
            velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //�������� ����

        if (!isMoveX2)
            velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

        Matrix rotY = XMMatrixRotationY(Rot().y);
        Vector3 direction = XMVector3TransformCoord(velocity, rotY);
        Rot().y = direction.y;

        Pos() += direction * moveSpeed * DELTA * -1;
    }
    
    */
    
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
        action = J_START;
        jumpVelocity = jumpForce;
        isJump = true;
        isSpace = true;
    }


    if (KEY_PRESS(VK_LSHIFT))
    {
        moveSpeed = 20;
        isRun = true;
    }

    velocity = w + a + s + d;
    velocity.Normalize();

    //���⼭���� �ٽú���
    Vector3 forward = Forward();
    Vector3 cross = Cross(forward, velocity);
    
   

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

    if (Pos().y > _ground+ 0.5f )
    {
        if (action != J_LOOP) action = J_LOOP;

        isJump = true;
    }
    else if (Pos().y < _ground )
    {

        //Pos().y = _ground;
        Pos().y = Lerp(Pos().y, _ground, 10*DELTA);
        jumpVelocity = 0;
        if (curState == J_LOOP) SetState(J_END);
        isJump = false;
        isSpace = false;
    }

}

void Player::AttackPal()
{
    // *�ѼҸ� ��� �ʿ�
    Ray ray;
    ray.pos = CAM->GlobalPos();
    ray.dir = CAM->Forward();
    Vector3 hitPoint;

    //Ray ray = CAM->ScreenPointToRay(mousePos);
    //Vector3 hitPoint;

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
    // ù��° �� ����
    PlayerPalsManager::Get()->SetSelPal(0);
    // �� ��ȯ
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
        if (select != 1)
        {
            SetState(R_DRAW);
            
        }
       
        if (isGaim)
        {
            SetState(R_Aim);
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


        return;
    }
    
   




    if (isJump)
    {
        SetState(J_START);
    }
    else if (isAiming)
    {
        SetState(S_AIM);

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
