#pragma once
class Tree
{
public:
    Tree(Transform* transform, bool one);
    ~Tree();

    void Update();
    void Render();
    void GUIRender();

    //void Place(Transform* transform);

    void Hit();

    //void Place(ModelInstancing* tree);
    void GetTem(Collider* collider);
    
    void SetImpostor();

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

    Item* test;
    Item* test2;
    Item* test3;
    Item* test4;
        
    bool isDead = false;

private:
    Transform* transform;

    //SphereCollider* collider;

    CapsuleCollider* collider;

    float Hp = 100;


    // �׽�Ʈ

    float Time = 0;
    Quad* impostor;
    Vector3 eyeDir;
    float theta;

    BlendState* blendState[2];
    bool isOne = true;

    float height = 12.654f;
};

