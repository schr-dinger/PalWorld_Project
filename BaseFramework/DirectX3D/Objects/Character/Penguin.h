#pragma once
class Penguin : public ModelAnimator, public Pal
//class Penguin : public Pal
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
    Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
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

    BlendState* blendState[2];
};

