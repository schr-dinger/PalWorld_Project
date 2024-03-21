#pragma once
class Tree
{
public:
    Tree(Transform* transform);
    ~Tree();

    void Update();
    void Render();
    void GUIRender();

    //void Place(Transform* transform);

    void Hit();

    //void Place(ModelInstancing* tree);
    void GetTem(Collider* collider);
    
    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

    Item* test;
    Item* test2;
    Item* test3;
    Item* test4;

private:
    Transform* transform;

    //SphereCollider* collider;

    CapsuleCollider* collider;

    float Hp = 100;


    // Å×½ºÆ®

    float Time = 0;
    Quad* Impostor;

    BlendState* blendState[2];
};

