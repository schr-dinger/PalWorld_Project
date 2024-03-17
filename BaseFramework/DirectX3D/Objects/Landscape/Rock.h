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

    Transform* GetTransform() { return transform; }
    SphereCollider* GetCollider() { return collider; }

    //BoxCollider* GetCollider() { return collider; }

private:
    Transform* transform;

    SphereCollider* collider;
    //BoxCollider* collider;

    float Hp = 200;
};

