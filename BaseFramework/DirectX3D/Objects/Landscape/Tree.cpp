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
		ItemManager::Get()->Mining(test);
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
	Hp -= 20.0f;
}

void Tree::GetTem(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		// 캐릭터 앞에 충돌체 키 입력시 애니메이션 후 충돌체 Active 충돌하면 힛하고 충돌체 off
		// 애니메이션이 끝나면 충돌체 off
		
		time += 2 * DELTA;
		

	}

	if (time > 2)
	{
		PlayerManager::Get()->GetPlayer()->GetMiningCol()->SetActive(false);
		Hit();
		time = 0;
	}

	
}
