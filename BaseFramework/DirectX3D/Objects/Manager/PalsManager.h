#pragma once
class PalsManager : public Singleton<PalsManager>
{
private:
    UINT SIZE = 100; // 매니저 안에서 굴릴 로봇 대수
    float SPAWN_TIME = 1.0f; // 로봇의 생성, 혹은 재생성에 필요한 시간

public:

    PalsManager();
    ~PalsManager();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    void SetTarget(Transform* target); //표적 설정
    void SetPlayer(Player* player); // 플레이어 설정


    bool IsCollision(Ray ray, Vector3& hitPoint); //충돌이 일어난 경우 판정

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
private:
    void OnGround(Terrain* terrain);
    void InsertMAI(string palModelName);
    void InsertAllMAI();
    void Collision(); // 세부 충돌 판정 진행
    void Spawn();     // (재)생성

private:
    Terrain* terrain;
    vector<ModelAnimatorInstancing*> palsInstancing;
    map<string, ModelAnimatorInstancing*> palsMAI;
    vector<Pal*> pals;

    Transform* target;
    Player* player;

    float time = 0; //경과된 시간

    // 알파값 빼기
    BlendState* blendState[2];

    // 테스트 : 히트 판정
    Vector3 testHit;
    bool testIsHit;
    int hitPalIndex;
};

