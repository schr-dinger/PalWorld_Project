#pragma once
class PalsManager : public Singleton<PalsManager>
{
private:
<<<<<<< Updated upstream
    UINT SIZE = 100; // 매니저 안에서 굴릴 로봇 대수
=======
    UINT SIZE = 50; // 매니저 안에서 굴릴 로봇 대수
>>>>>>> Stashed changes
    float SPAWN_TIME = 0.1f; // 로봇의 생성, 혹은 재생성에 필요한 시간

public:

    PalsManager();
    ~PalsManager();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    void SetTarget(Transform* target); //표적 설정

    bool IsCollision(Ray ray, Vector3& hitPoint); //충돌이 일어난 경우 판정

    void OnGround(Terrain* terrain);

private:
    void InsertMAI(string palModelName);
    void Collision(); // 세부 충돌 판정 진행
    void Spawn();     // (재)생성

private:

    vector<ModelAnimatorInstancing*> palsInstancing;
    vector<Pal*> pals;

    Transform* target;

    float time = 0; //경과된 시간

    // 알파값 빼기
    BlendState* blendState[2];

};

