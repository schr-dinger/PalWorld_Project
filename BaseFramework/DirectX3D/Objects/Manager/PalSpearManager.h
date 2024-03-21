#pragma once
class PalSpearManager : public Singleton<PalSpearManager>
{
private:
    friend class Singleton;
    UINT SIZE = 10; // ���ÿ� ��ô ������ �Ƚ��Ǿ� �ִ� ����

public:
    PalSpearManager();
    ~PalSpearManager();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void Throw(Vector3 pos, Vector3 dir); //���� ��ü���� �����ϱ� ���� �Ű� �Լ�

    bool IsCollision(Collider* collider, class Pal* pal); //�� �Ƚ��Ǿ �ٸ� ��ü�� �浹�ߴ��� �Ǻ��ϱ� ����

    void SetTerrain(class Terrain* terrain);

    int GetSize() {return palSpears.size();}

    deque<PalSpear*>& GetPalSpears() { return palSpears; }

private:
    //���� ��¿� ��
    ModelInstancing* palSpearInstancing; //���� ��
    deque<PalSpear*> palSpears; // ���̵� (����)

    class Terrain* terrain; 

    // ���� �� ������� ������� �� �� ��
    //Texture* palWhiteTexture;
    //Pal* catchingPal;

};

