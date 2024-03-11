#pragma once
class PalSpearManager : public Singleton<PalSpearManager>
{
private:
    friend class Singleton;
    UINT SIZE = 3; // ���ÿ� ��ô ������ �Ƚ��Ǿ� �ִ� ����

public:
    PalSpearManager();
    ~PalSpearManager();

    void Update();
    void Render();
    void GUIRender();

    void Throw(Vector3 pos, Vector3 dir); //���� ��ü���� �����ϱ� ���� �Ű� �Լ�

    bool IsCollision(Collider* collider, class Pal* pal); //�� �Ƚ��Ǿ �ٸ� ��ü�� �浹�ߴ��� �Ǻ��ϱ� ����

    void SetTerrain(class Terrain* terrain);


private:
    //���� ��¿� ��
    ModelInstancing* palSpearInstancing; //���� ��
    vector<PalSpear*> palSpears; // ���̵� (����)

    class Terrain* terrain; 

    // ���� �� ������� ������� �� �� ��
    Texture* palWhiteTexture;
    Pal* catchingPal;

};

