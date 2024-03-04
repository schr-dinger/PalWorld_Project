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

private:
    Transform* transform;

    SphereCollider* collider;

    float Hp = 200;
};

