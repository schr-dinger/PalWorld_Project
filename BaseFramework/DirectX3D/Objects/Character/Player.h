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
    void SetAnimation();
    void SetState(ACTION state);
    void Jump(float _ground);

public:
    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

private:
    ACTION action;
    ACTION curState = ACTION::IDLE;


    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 };

    Vector3 velocity;

    float moveSpeed = 10;
    float rotSpeed = 1;
    float deceleration = 5;

    float jumpVelocity = 0;
    float jumpForce = 0.03f;
    float gravityMult = 0.005f;
    bool isJump = false;
    bool isSpace = false;

    Terrain* terrain;
};

