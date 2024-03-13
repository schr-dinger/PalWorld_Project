#pragma once
class PlayerPalsManager : public Singleton<PlayerPalsManager>
{
    // �÷��̾ ���� ����� ��, �� �Ŵ����� �ִ� ���� ���� �����ؼ� ���⿡ �־��ֱ� ���� �Ŵ���
    // �� �Ŵ����� �ٸ��� ���⼱ ��� �ȵ� ������Ʈ �� ���� ����, ������(��ȯ��) �ȸ� ������Ʈ �� ����

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

    //void SetTarget(Transform* target); //ǥ�� ����
    void SetTarget(); //ǥ�� ����

    void SetPlayer(Player* player); // �÷��̾� ����

    bool IsCollision(Ray ray, Vector3& hitPoint); //�浹�� �Ͼ ��� ����

    void Caught(Pal* CaughtPal); // ��ȹ

    // ��ȯ �׽�Ʈ��
    void SetSelPal(int selPal) { this->selPal = selPal; }

    void Summons();     // ��ȯ
    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

    Pal* GetPal(int num) { return pals[num]; }

    vector<Pal*>& GetPalvector() { return pals; }
    Vector3 destPos;

    int GetPathSize() { return path.size(); }

    void SetMode(MODE mode) { this->mode = mode; }

private:
    void OnGround(Terrain* terrain);
    void InsertAllMAI();
    void Collision(); // ���� �浹 ���� ����

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

    float time = 0; //����� �ð�

    // ���İ� ����
    BlendState* blendState[2];

    float pathTime = 0;

    vector<Vector3> path;
    //Vector3 velocity;

    float smallest;
    Pal* closePal;

};

