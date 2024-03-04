#pragma once
class Player : public ModelAnimator
{
private:
    enum ACTION
    {
        IDLE,
        WALK,
        RUN,

        J_START,
        J_END,
        J_LOOP,

        R_IDLE,
        R_RUN,
        R_Aim,
        R_RELOAD,
        R_DRAW,

        RA_FWD,
        //RA_BACK,
        //RA_LEFT,
        //RA_RIGHT,

        S_AIM,
        S_THROW

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


private:
    ACTION action;
    ACTION curState = ACTION::IDLE;

    Transform* CamTransform;
    Transform* Hand;

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
    bool isRun = false;




    Model* Gun;

    Terrain* terrain;

    // 테스트 : 포획
    SphereCollider* testPalSpear;


    // 무기 조준

    ParticleSystem* particle;
    bool isGun = false;
    bool isGaim = false;
    int select = 0;
    //Bullet* bullet;




    Vector3 ogCam = { -0.05,1.7,2.5 };
    Vector3 foCam = { -0.03,1.3,1.0 };
};

