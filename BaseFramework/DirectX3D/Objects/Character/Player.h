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
    void Jump();

private:
    ACTION action;

    float moveSpeed = 0;
    float jumpVelocity = 0;
    float jumpForce = 0.5f;
    float gravityMult = 0.5f;
    bool isJump = false;

};

