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

    // 필드 팔 상호작용 함수
    void AttackPal();
    void CatchPal();
    void SummonsPal();

public:
    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

    SphereCollider* GetPalSpearCol() { return testPalSpear; }

    Transform* GetFrontPoint() { return frontPoint ; }

private:
    ACTION action;
    ACTION curState = ACTION::IDLE;

    Transform* CamTransform;

    Transform* frontPoint;

    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 };

    Vector3 velocity;

    Vector3 w;
    Vector3 a;
    Vector3 s;
    Vector3 d;

    Vector3 z = { 0,0,0 };

    float moveSpeed = 10;
    float rotSpeed = 1;
    float deceleration = 5;

    float jumpVelocity = 0;
    float jumpForce = 0.03f;
    float gravityMult = 0.005f;
    bool isJump = false;
    bool isSpace = false;
    bool isAiming = false;
    Terrain* terrain;

    bool test = true;

    // 테스트 : 포획
    SphereCollider* testPalSpear;
    SphereCollider* testFrontSphere;

    Vector3 ogCam = { -0.05,1.7,2.5 };
    Vector3 foCam = { -0.03,1.3,1.0 };
};

