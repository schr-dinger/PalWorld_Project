#include "Framework.h"

Tree::Tree(Transform* transform) :transform(transform)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;
		
	matter = new Ingredient(1);
	
}

Tree::~Tree()
{
	delete collider;
	delete matter;
	
}

void Tree::Update()
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

void Tree::Render()
{
	if (!transform->Active()) return;

	collider->Render();


}

void Tree::GUIRender()
{

	ImGui::Text("Hp : %d", &Hp);


}

//void Tree::Place(Transform* transform)
//{
//}

void Tree::Hit()
{
	Hp -= 60.0f;
}

void Tree::GetTem(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		// ĳ���� �տ� �浹ü Ű �Է½� �ִϸ��̼� �� �浹ü Active �浹�ϸ� ���ϰ� �浹ü off
		// �ִϸ��̼��� ������ �浹ü off
		
		time += 2 * DELTA;
		

	}

	if (time > 2)
	{
		PlayerManager::Get()->GetPlayer()->GetMiningCol()->SetActive(false);
		Hit();
		time = 0;
	}

	
}
