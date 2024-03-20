#pragma once
class Rock
{
public:
    Rock(Transform* transform);
    ~Rock();

    void Update();
    void Render();
    void GUIRender();

    void Hit();
    void GetTem(Collider* collider);

    Transform* GetTransform() { return transform; }
    SphereCollider* GetCollider() { return collider; }

    //BoxCollider* GetCollider() { return collider; }

private:
    Transform* transform;

    SphereCollider* collider;
    //BoxCollider* collider;

    Item* matter;
    float Hp = 200;

    float time = 0;
};

