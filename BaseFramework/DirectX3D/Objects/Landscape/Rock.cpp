#include "Framework.h"

Rock::Rock(Transform* transform) : transform(transform)
{
    collider = new SphereCollider();
    //collider = new BoxCollider();

    collider->SetParent(transform);
    collider->Scale() *= 200.0f;

    matter = new Ingredient(2);
}

Rock::~Rock()
{
    delete collider;
    delete matter;
}

void Rock::Update()
{
    if (!transform->Active()) return;

    if (Hp < 0.0f)
    {
        transform->SetActive(false);
        ItemManager::Get()->Mining(matter);
    }

    GetTem(PlayerManager::Get()->GetPlayer()->GetMiningCol());

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

void Rock::GetTem(Collider* Pcollider)
{
    if (!Pcollider->Active()) return;

    if (this->collider->IsCollision(Pcollider))
    {
        Hit();
        Pcollider->SetActive(false);
    }



}
