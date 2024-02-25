#pragma once
class PlayerPalsManager : public Singleton<PlayerPalsManager>
{
    // �÷��̾ ���� ����� ��, �� �Ŵ����� �ִ� ���� ���� �����ؼ� ���⿡ �־��ֱ� ���� �Ŵ���
    // �� �Ŵ����� �ٸ��� ���⼱ ��� �ȵ� ������Ʈ �� ���� ����, ������(��ȯ��) �ȸ� ������Ʈ �� ����

public:

    PlayerPalsManager();
    ~PlayerPalsManager();

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
    void InsertAllMAI();
    void Collision(); // ���� �浹 ���� ����
    void Summons();     // ��ȯ
    void Caught(Pal* CaughtPal);

private:
    Terrain* terrain;
    map<string, ModelAnimatorInstancing*> palsMAI;
    vector<Pal*> pals;
    int selPal;
    map<string, int> palsMAIIndex;

    Transform* target;
    Player* player;

    float time = 0; //����� �ð�

   

    // ���İ� ����
    BlendState* blendState[2];


};

