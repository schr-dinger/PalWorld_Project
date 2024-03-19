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
		// ĳ���� �տ� �浹ü Ű �Է½� �ִϸ��̼� �� �浹ü Active �浹�ϸ� ���ϰ� �浹ü off
		// �ִϸ��̼��� ������ �浹ü off

		// if(PlayerManager::Get()->GetPlayer()->)


	}


	
}
