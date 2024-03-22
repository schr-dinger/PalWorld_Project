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
    void GetTem(Collider* Pcollider);
    
    void SetImpostor();

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

    Item* matter;
    bool isDead = false;

private:
    Transform* transform;

    //SphereCollider* collider;

    CapsuleCollider* collider;

    float Hp = 100;


    // Å×½ºÆ®

    float Time = 0;
    Quad* impostor;
    Vector3 eyeDir;
    float theta;

    BlendState* blendState[2];
    bool isOne = true;

    float height = 12.654f;
};

