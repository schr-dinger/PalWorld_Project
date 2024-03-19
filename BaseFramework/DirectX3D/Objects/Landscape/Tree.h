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
    

private:
    Transform* transform;

    //SphereCollider* collider;

    CapsuleCollider* collider;

    float Hp = 100;

   

};

