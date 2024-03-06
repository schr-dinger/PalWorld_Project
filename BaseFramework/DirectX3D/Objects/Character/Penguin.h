#pragma once
class Penguin : public Pal
{
private:
    enum class ACTION
    {
        IDLE,
        WALK,
        RUN,
        ATTACK,
        DAMAGE,
        WORK
    };

public:
    Penguin(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Penguin();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();
    Texture* GetTexture() { return icon; }
    float GetCurHp() { return curHP / maxHP; }

    // �׼� : ����
    void Attack();      // �� �� ����
    void FieldAttack(); // �ʵ� �� ����

    // �׼� : ���±�
    void Damage();

    // �׼� : �����Ǳ�
    void Spawn(Vector3 pos);

    // ��ȯ�ϱ� : �÷��̾ �� ��ȯ��
    void Summons(Vector3 pos);


    //ǥ�� ����
    void SetTarget(Transform* target);

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

private:
    //void ClipSync(); // �����ص� �����ҵ�
    
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    // ���� ������ �����ϴ� �Լ�(��ȯ, ��� ��� �ʿ�)
    //void EndStandUp();
    void EndAttack();
    void EndDamage(); // Hit ������ enum�� ��Ī ��ġ��Ű��
                      // -> ���� ��� �� ������ �� ���ΰ�
    //void EndDying();

    void SetAction(ACTION action);

    void Move();
    void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ

private:
    //�������
    Transform* transform;
    CapsuleCollider* collider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    Transform* target;

    float speed; //�ӷ� : �⺻ ����
    float maxHP;
    float curHP;

    Vector3 velocity; //�ӷ� : ���� ������

    UINT index; //�κ��� ���� �ε���

    //������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    // �� UI��(����, ü�� ��)
    ProgressBar* hpBar;

    Vector3 barPos; //ü�¹ٰ� ��ġ�� ��

    //������� ����, �θ𿡼� ���� ���� �͵�

    ACTION action = ACTION::IDLE; 
    // -> �θ�� �̵� ����, �̵���
    //    ���̵�, �۾����� Ư�� ������ enum �ڷ� ����

    int tmpN;
};

