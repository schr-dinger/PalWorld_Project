#include "Framework.h"

Player::Player() :	ModelAnimator("NPC")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Pos() = { 20, 20, 20 };


    ReadClip("B_Idle");
    ReadClip("B_Walk");
    ReadClip("B_Run");
   
    ReadClip("J_Start");
    ReadClip("J_End");
    ReadClip("J_DownLoop");

    ReadClip("Rifle_idle");
    ReadClip("Rifle_reload");
    ReadClip("Rifle_run");
    ReadClip("Rifle_draw");
    ReadClip("Rifle_Aim");
    

    ReadClip("S_Aim");
    ReadClip("S_Idle");
    ReadClip("S_Run");
    ReadClip("S_Throw");




    Scale() *= 0.01f;

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);

    // Å×½ºÆ® : ÆÈ Æ÷È¹
    testPalSpear = new SphereCollider(0.2f);
    testPalSpear->SetActive(false);

    // Å×½ºÆ® ÃÑ
    Hand = new Transform();

    Gun = new Model("Rifle");
    
    Gun->SetParent(Hand);
    
    Gun->Rot().x += 1.5f;
    Gun->Rot().y -= 0.10f;
    

    



    GetClip(ACTION::J_START)->SetEvent(bind(&Player::SetState, this,J_LOOP),0.5f);
    GetClip(ACTION::J_END)->SetEvent(bind(&Player::SetState, this, IDLE), 0.2f);
    GetClip(ACTION::S_THROW)->SetEvent(bind(&Player::SetState, this, IDLE), 0.2f);

    

}

Player::~Player()
{

}

void Player::Update()
{
    //ClipSync();
    Hand->SetWorld(GetTransformByNode(68));

    
    Control();
    SetAnimation();
    
    Gun->UpdateWorld();
    ModelAnimator::Update();

    
    
}

void Player::Render()
{
    testPalSpear->Render();

    Gun->Render();
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

    // Å×½ºÆ® : ÆÈ Æ÷È¹, ÆÈÀ» ¸ÂÃèÀ» ¶§¸¸ ÆÈ½ºÇÇ¾î ÄÝ¶óÀÌ´õ È°¼ºÈ­
    testPalSpear->SetActive(false);

    if (KEY_PRESS('V'))
    {

        Rotate();
                
        if (!isThrow)
        {
            SetState(S_AIM);
        }
                
        if (KEY_DOWN(VK_LBUTTON)) // ÆÈ °ø°Ý
        {
            AttackPal();
        }
        else if (KEY_DOWN(VK_RBUTTON)) // ÆÈ Æ÷È¹
        {
            isThrow = true;
            SetState(S_THROW);
            CatchPal();
        }
        else if (KEY_DOWN('Z')) // Æ÷È¹ÇÑ ÆÈ ¼ÒÈ¯
        {
            SummonsPal();
        }
    }
    else if (KEY_UP('V'))
    {
        isThrow = false;
        SetState(IDLE);
    }
   
    if (KEY_PRESS(VK_RBUTTON))
    {
        SetState(R_Aim);
    }
    else if (KEY_UP(VK_RBUTTON))
    {
        SetState(IDLE);
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
        
        jumpVelocity = jumpForce;
        isJump = true;
        isSpace = true;
    }


    if (velocity.Length() > 1) velocity.Normalize();

    if (!isMoveZ)
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //º¸°£À¸·Î °¨¼Ó

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

    if (Pos().y > _ground+0.5f )
    {
        if (curState != J_LOOP) SetState(J_LOOP);

        isJump = true;
    }

    if (Pos().y < _ground )
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
    // *ÃÑ¼Ò¸® Ãâ·Â ÇÊ¿ä

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Vector3 hitPoint;

    

    if (PalsManager::Get()->IsCollision(ray, hitPoint))
    {
        // ÅÂ½ºÆ® : È÷Æ®
        
        // ÇÃ·¹ÀÌ¾î¿¡ ÃÑ ¸Â´Â ÀÌÆåÆ® µî Ãß°¡ ÇÊ¿ä

        // ÀÌÆåÆ®´Â È÷Æ® Æ÷ÀÎÆ®¿¡¼­ Ãâ·Â
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
    // Ã¹¹øÂ° ÆÈ ¼±ÅÃ
    PlayerPalsManager::Get()->SetSelPal(0);
    // ÆÈ ¼ÒÈ¯
    PlayerPalsManager::Get()->Summons();
}

void Player::SetAnimation()
{
    if (curState == J_LOOP)
    {
        
        ClipOnce();
        return;
    }
    if (curState == S_AIM|| curState == S_THROW|| curState == R_Aim)
    {
        return;
    }


    if (isJump)
    {
        SetState(J_START);
    }
    else
    {
        if (velocity.z > 0.1f)
            SetState(WALK);
        else if (velocity.z < -0.1f)
            SetState(WALK);
        else if (velocity.x > 0.1f)
            SetState(WALK);
        else if (velocity.x < -0.1f)
            SetState(WALK);
        else SetState(IDLE);
        
    }
    

    ////////////////////////

    // test

    if (KEY_DOWN('1'))
    {
        SetState(R_DRAW);
    }


}

void Player::SetState(ACTION state)
{
    if (state == curState) return;

    curState = state;
    PlayClip((int)state);

}
