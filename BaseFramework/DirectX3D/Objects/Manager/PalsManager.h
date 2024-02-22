#pragma once
class PalsManager : public Singleton<PalsManager>
{
private:
    UINT SIZE = 30; // �Ŵ��� �ȿ��� ���� �κ� ���
    float SPAWN_TIME = 2; // �κ��� ����, Ȥ�� ������� �ʿ��� �ð�

public:

    PalsManager();
    ~PalsManager();

    void Update();
    void Render();
    void PostRender();

    void SetTarget(Transform* target); //ǥ�� ����

    bool IsCollision(Ray ray, Vector3& hitPoint); //�浹�� �Ͼ ��� ����

private:
    void InsertMAI(string palModelName);
    void Collision(); // ���� �浹 ���� ����
    void Spawn();     // (��)����

private:

    vector<ModelAnimatorInstancing*> palsInstancing;
    vector<Pal*> pals;

    Transform* target;

    float time = 0; //����� �ð�

};

