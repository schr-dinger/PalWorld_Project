#pragma once
class Player : public ModelAnimator
{
private:
    enum ACTION
    {
        IDLE,
        WALK,
        //RUN,
        //
        //J_START,
        //J_END,
        //J_LOOP,
        //
        //R_IDLE,
        //R_RUN,
        //R_Aim,
        //R_RELOAD,
        //R_DRAW,
        //
        //RA_FWD,
        //
        //BW_AIM,
        //BW_FIRE,
        //
        M_MINING,
        //M_ATTACK,
        //
        //S_AIM,
        //S_THROW,

        // BW_AIM

    };

public:
    Player();
    ~Player();

    void Update();
    void Render();
    void ShadowRender();
    void GUIRender();

    // 장비창 넘버 가져오기
    int GetWepSel() { return select; }

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
    void ThrowPalSpear(); // 팰 소환할때 던지기

    //
    void MState() { MiningCollider->SetActive(false); } // 애니메이션 끝나면 넣는 용도

public:
    SphereCollider* GetPalSpearCol() { return testPalSpear; }

    CapsuleCollider* GetPlayerCol() { return playerCollider; }

    Transform* GetFrontPoint() { return frontPoint; }

    Transform* GetHand() { return Hand; }
    SphereCollider* GetMiningCol() { return MiningCollider; }

    void UiMode();

    void SetModel(int num, Model* model) { weapons[num] = model; }
    // Model* GetModel() { return weapon; }
private:
    ACTION action;
    ACTION curState = ACTION::IDLE;

    Transform* CamTransform;
    Transform* Hand;

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
    bool isRun = false;

    bool test = true;
    bool UiOn = false;


    // 테스트 : 팰 스피어 던지기 관련
    SphereCollider* testPalSpear;
    SphereCollider* testFrontSphere;
    Model* summonPalSpear;
    Model* summonPalSpearThrow;
    SphereCollider* summonPalSpearCollider;
    Vector3 summonPalSpearDIr;
    float speed = 20;
    // 팰스피어 중력
    float gravi = 9.8f;
    float downForce = 0;
    Vector3 down = { 0, -1, 0 };


    Vector3 ogCam = { -0.05,1.7,2.5 };
    Vector3 foCam = { -0.3,1.35,1.0 };


    // 무기 조준

    ParticleSystem* particle;
    bool isGun = false;
    bool isGaim = false;

    bool isBow = false;
    bool isBaim = false;

    bool Picking = false;
    bool W_Aiming = false;
    int select = 1;
   
    vector<Model*> weapons;

    //player collider

    CapsuleCollider* playerCollider;

    // Mining 
    SphereCollider* MiningCollider;
};

