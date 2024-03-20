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
    Hp -= 110.0f;
}

void Rock::GetTem(Collider* collider)
{

    if (this->collider->IsCollision(collider))
    {
        // 캐릭터 앞에 충돌체 키 입력시 애니메이션 후 충돌체 Active 충돌하면 힛하고 충돌체 off
        // 애니메이션이 끝나면 충돌체 off

        time += 3 * DELTA;


    }

    if (time > 2)
    {
        PlayerManager::Get()->GetPlayer()->GetMiningCol()->SetActive(false);
        Hit();
        time = 0;
    }






}
