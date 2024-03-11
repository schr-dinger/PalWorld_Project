#pragma once
class PalSpear
{
    //����ü �ϳ��� �Ѱ��ϴ� Ŭ����

private:
    //������ �ʿ��� �ֿ� ������ (������)
    float LIFE_SPAN = 1.0f; // life span = ���� �ֱ�, Ȥ�� ���� ���� �Ⱓ
                         // ���α׷��ֿ����� �ӽ÷� ������ ��ü�� �ڵ� ����
                         // Ȥ�� ��Ȱ��ȭ�ϱ���� �ɸ��� �ð��� ���Ѵ�

public:
    enum class State
    {
        THROW,
        HITPAL,
        CATCHING,
        SUCCESS,
        FAIL
    };

public:
    //ȣ��� �Լ�
    PalSpear(Transform* transform); //�ν��Ͻ��� ������ Ʈ������ �Ű� ����
    ~PalSpear();

    void Update();
    void Render();
    void GUIRender();

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTerrain(class Terrain* terrain) { this->terrain = terrain; }
    void SetPal(class Pal* pal) { this->pal = pal; }
    void SetState(State state) { this->state = state; }
private:
    //��� �Լ�
    void StateThrow();
    void StateHitPal();
    void StateCatching();
    void StateSuccess();
    void StateFail();
private:
    //��� ����

    Transform* transform;
    SphereCollider* collider;

    float speed = 15;
    float time = 0; //������ �ð�

    Vector3 direction;

    // �߷�
    float gravi = 9.8f;
    //float gravi = 30;
    float downForce = 0;
    Vector3 down = { 0, -1, 0 };

    class Terrain* terrain;

    State state;

    class Pal* pal;
    
};

