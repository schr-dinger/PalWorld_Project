#include "Framework.h"

Rock::Rock(Transform* transform) : transform(transform)
{
    collider = new SphereCollider();
    //collider = new BoxCollider();

    collider->SetParent(transform);
    collider->Scale() *= 200.0f;

}

Rock::~Rock()
{
    delete collider;
}

void Rock::Update()
{
    if (!transform->Active()) return;

    if (Hp < 0.0f)
    {
        transform->SetActive(false);
    }

    transform->UpdateWorld();
    collider->UpdateWorld();
}

void Rock::Render()
{
    if (!transform->Active()) return;

    collider->Render();
}

void Rock::GUIRender()
{
}

void Rock::Hit()
{
    Hp -= 20.0f;
}
