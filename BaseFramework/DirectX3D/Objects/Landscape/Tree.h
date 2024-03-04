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


    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

private:
    Transform* transform;

    //SphereCollider* collider;

    CapsuleCollider* collider;


    float Hp = 100;
};

