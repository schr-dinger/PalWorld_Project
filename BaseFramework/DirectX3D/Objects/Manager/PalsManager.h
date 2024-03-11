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
    void SetPlayer(Player* player); // �÷��̾� ����


    bool IsCollision(Ray ray, Vector3& hitPoint); //�浹�� �Ͼ ��� ����

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
private:
    void OnGround(Terrain* terrain);
    void InsertMAI(string palModelName);
    void InsertAllMAI();
    void Collision(); // ���� �浹 ���� ����
    void Spawn();     // (��)����

    void PathCollider();
private:
    Terrain* terrain;
    vector<ModelAnimatorInstancing*> palsInstancing;
    map<string, ModelAnimatorInstancing*> palsMAI;
    vector<Pal*> pals;

    Transform* target;
    Player* player;

    float time = 0; //����� �ð�

    // ���İ� ����
    BlendState* blendState[2];

    // �׽�Ʈ : ��Ʈ ����
    Vector3 testHit;
    bool testIsHit;
    int hitPalIndex;

    // �׽�Ʈ : �ȳ��� �浹
    vector<Vector3> lastPos;
};

