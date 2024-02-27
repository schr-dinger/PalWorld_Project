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
        R_RELOAD,
        R_DRAW,
        R_Aim,
        // ATTACK,
        
        
        //DRAW,
        
        S_AIM,
        S_IDLE,
        S_RUN,
        S_THROW

    };

public:
    Player();
    ~Player();

    void Update();
    void Render();
    void GUIRender();


    Model* GetModel() { return Gun; }

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
    ACTION curState = IDLE;

    Model* Gun;
    Transform* Hand;

    POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 };

    Vector3 velocity;

    float moveSpeed = 30;
    float rotSpeed = 1;
    float deceleration = 5;

    float jumpVelocity = 0;
    float jumpForce = 0.05f;
    float gravityMult = 0.005f;
    bool isJump = false;
    bool isSpace = false;
    bool isThrow = false;

    Terrain* terrain;

    // 테스트 : 포획
    SphereCollider* testPalSpear;

    // 테스트 노드 확인
    int node = 0;
};

