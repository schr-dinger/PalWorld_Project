#pragma once
class PlayerPalsManager : public Singleton<PlayerPalsManager>
{
    // 플레이어가 팔을 잡았을 때, 팔 매니저에 있는 팔을 깊은 복사해서 여기에 넣어주기 위한 매니저
    // 팔 매니저와 다르게 여기선 모든 팔들 업데이트 및 랜더 안함, 선택한(소환한) 팔만 업데이트 및 랜더

public:

    enum class MODE
    {
        PASSIVE,
        AGGRESSIVE,
    };

public:

    PlayerPalsManager();
    ~PlayerPalsManager();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    //void SetTarget(Transform* target); //표적 설정
    void SetTarget(); //표적 설정

    void SetPlayer(Player* player); // 플레이어 설정

    bool IsCollision(Ray ray, Vector3& hitPoint); //충돌이 일어난 경우 판정

    void Caught(Pal* CaughtPal); // 포획

    // 소환 테스트용
    void SetSelPal(int selPal) { this->selPal = selPal; }

    void Summons();     // 소환
    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

    Pal* GetPal(int num) { return pals[num]; }

    vector<Pal*>& GetPalvector() { return pals; }
    Vector3 destPos;

    int GetPathSize() { return path.size(); }

    void SetMode(MODE mode) { this->mode = mode; }

private:
    void OnGround(Terrain* terrain);
    void InsertAllMAI();
    void Collision(); // 세부 충돌 판정 진행

    void PathFinding();

    void SetPath();
    void Move();

private:
    Terrain* terrain;
    map<string, ModelAnimatorInstancing*> palsMAI;
    vector<Pal*> pals;
    int selPal;
    map<string, int> palsMAIIndex;
    
    //Transform* target;
    Player* player;

    MODE mode = MODE::PASSIVE;
    //MODE mode = MODE::AGGRESSIVE;

    float time = 0; //경과된 시간

    // 알파값 빼기
    BlendState* blendState[2];

    float pathTime = 0;

    vector<Vector3> path;
    //Vector3 velocity;

    float smallest;
    Pal* closePal;

};

