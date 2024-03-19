#include "Framework.h"

Tree::Tree(Transform* transform) :transform(transform)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;

	test = new Equipment(1);
	test2 = new Equipment(2);
	test3 = new Ingredient(1);
	test4 = new Ingredient(2);

}

Tree::~Tree()
{
	delete collider;
	delete test;
	delete test2;
	delete test3;
	delete test4;
}

void Tree::Update()
{
	if (!transform->Active()) return;

	if (Hp < 0.0f)
	{
		transform->SetActive(false);
	}



	GetTem(PlayerManager::Get()->GetPlayer()->GetPlayerCol());

	transform->UpdateWorld();
	collider->UpdateWorld();
}

void Tree::Render()
{
	if (!transform->Active()) return;

	collider->Render();
}

void Tree::GUIRender()
{




}

//void Tree::Place(Transform* transform)
//{
//}

void Tree::Hit()
{
	Hp -= 20.0f;
}

void Tree::GetTem(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		Time += 3 * DELTA;

	}



	if (Time > 5)
	{
		ItemManager::Get()->Mining(test);
		ItemManager::Get()->Mining(test2);
		ItemManager::Get()->Mining(test3);
		ItemManager::Get()->Mining(test4);
		//test2 = nullptr;
		Time = 0;
	}

}
