#include "Framework.h"

Tree::Tree(Transform* transform) :transform(transform)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;

	
	test = new Ingredient(1);
	
}

Tree::~Tree()
{
	delete collider;
	delete test;
	
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

	if (Hp <= 0)
	{
		if(transform->Active()) ItemManager::Get()->Mining(test);
	
	}
	


}

void Tree::GetTem(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		// 캐릭터 앞에 충돌체 키 입력시 애니메이션 후 충돌체 Active 충돌하면 힛하고 충돌체 off
		// 애니메이션이 끝나면 충돌체 off

		// if(PlayerManager::Get()->GetPlayer()->)


	}


	
}
