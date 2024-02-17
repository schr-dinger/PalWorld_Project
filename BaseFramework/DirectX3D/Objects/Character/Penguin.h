#pragma once
class Penguin : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        WALK,
        RUN,
        ATTACK,
        DAMAGE,
        WORK
    };

public:
    Penguin();
    ~Penguin();

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

