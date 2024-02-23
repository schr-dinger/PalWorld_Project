#pragma once
class PalsManager : public Singleton<PalsManager>
{
private:
    UINT SIZE = 50; // �Ŵ��� �ȿ��� ���� �κ� ���
    float SPAWN_TIME = 0.1f; // �κ��� ����, Ȥ�� ������� �ʿ��� �ð�

public:

    PalsManager();
    ~PalsManager();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    void SetTarget(Transform* target); //ǥ�� ����

    bool IsCollision(Ray ray, Vector3& hitPoint); //�浹�� �Ͼ ��� ����

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
private:
    void OnGround(Terrain* terrain);
    void InsertMAI(string palModelName);
    void Collision(); // ���� �浹 ���� ����
    void Spawn();     // (��)����

private:
    Terrain* terrain;
    vector<ModelAnimatorInstancing*> palsInstancing;
    vector<Pal*> pals;

    Transform* target;

    float time = 0; //����� �ð�

    // ���İ� ����
    BlendState* blendState[2];

};

