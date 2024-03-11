#pragma once
class PalSpearManager : public Singleton<PalSpearManager>
{
private:
    friend class Singleton;
    UINT SIZE = 3; // 동시에 투척 가능한 팔스피어 최대 개수

public:
    PalSpearManager();
    ~PalSpearManager();

    void Update();
    void Render();
    void GUIRender();

    void Throw(Vector3 pos, Vector3 dir); //개별 객체에게 전달하기 위한 매개 함수

    bool IsCollision(Collider* collider, class Pal* pal); //각 팔스피어가 다른 물체와 충돌했는지 판별하기 위함

    void SetTerrain(class Terrain* terrain);


private:
    //쿠나이 출력용 모델
    ModelInstancing* palSpearInstancing; //쿠나이 모델
    vector<PalSpear*> palSpears; // 쿠나이들 (벡터)

    class Terrain* terrain; 

    // 잡은 팰 흰색으로 출력해줄 새 모델 델
    Texture* palWhiteTexture;
    Pal* catchingPal;

};

