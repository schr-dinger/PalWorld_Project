#pragma once
class PlayerPalsManager : public Singleton<PlayerPalsManager>
{
    // 플레이어가 팔을 잡았을 때, 팔 매니저에 있는 팔을 깊은 복사해서 여기에 넣어주기 위한 매니저

public:

    PlayerPalsManager();
    ~PlayerPalsManager();

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
    void InsertAllMAI();
    void Collision(); // 세부 충돌 판정 진행
    void Summons();     // 소환

private:
    Terrain* terrain;
    vector<ModelAnimatorInstancing*> palsInstancing;
    map<string, ModelAnimatorInstancing*> palsMAI;
    vector<Pal*> pals;

    Transform* target;
    Player* player;

    float time = 0; //경과된 시간

    int selPal;

    // 알파값 빼기
    BlendState* blendState[2];


};

