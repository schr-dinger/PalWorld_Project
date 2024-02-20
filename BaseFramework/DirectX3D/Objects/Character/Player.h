#pragma once
class Player : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        WALKF,
        WALKR,
        WALKL,
        RUNF,
        RUNR,
        RUNL,
        JUMP,
        ATTACK,
        DAMAGE,
        DRAW,
        AIM,
        SHOOT
    };

public:
    Player();
    ~Player();

    void Update();
    void Render();
    void GUIRender();

private:
    void ClipSync();
    void Control();
    void Move();
    void Rotate();
    void Jump();

    void SetAnimation();
    void SetState(ACTION state);

private:
    ACTION action;
    ACTION curState = ACTION::IDLE;


    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 };

    Vector3 velocity;

    float moveSpeed = 50;
    float rotSpeed = 1;
    float deceleration = 5;

    float jumpVelocity = 0;
    float jumpForce = 0.5f;
    float gravityMult = 0.5f;
    bool isJump = false;

};

