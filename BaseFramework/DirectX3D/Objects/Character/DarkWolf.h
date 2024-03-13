#pragma once
class DarkWolf : public Pal
{
private:
    enum class ACTION
    {
        IDLE,
        WALK,
        RUN,
        ATTACK,
        DAMAGE,
    };

public:
    DarkWolf(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~DarkWolf();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();
    Texture* GetTexture() { return icon; }
    Texture* GetTextureC() { return iconC; }
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
    ModelAnimatorInstancing* GetInstancing() { return instancing; }


private:

    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    // ���� ������ �����ϴ� �Լ�(��ȯ, ��� ��� �ʿ�)
    void EndAttack();
    void EndDamage(); // Hit ������ enum�� ��Ī ��ġ��Ű��

    void SetAction(ACTION action);

    void Move();
    void MoveP();

    void UpdateUI();

private:
    Transform* transform;
    CapsuleCollider* collider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    Transform* target;

    float speed;
    float maxHP;
    float curHP;

    UINT index;

    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    ProgressBar* hpBar;

    Vector3 barPos;


    ACTION action = ACTION::IDLE;
    int tmpN;

};

