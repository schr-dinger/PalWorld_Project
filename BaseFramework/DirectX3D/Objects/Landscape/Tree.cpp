#include "Framework.h"

Tree::Tree(Transform* transform) :transform(transform)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;

	test = new Equipment(1);
	test2 = new Equipment(2);
	test3 = new Ingredient(2);
	test4 = new Equipment(3);

	Impostor = new Quad(Vector2(50.0f, 50.0f));
	Impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/Tree2/tree2I_1A.png");

	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);

}

Tree::~Tree()
{
	delete collider;
	delete test;
	delete test2;
	delete test3;
	delete test4;

	delete Impostor;
	FOR(2)
	{
		delete blendState[i];
	}
}

void Tree::Update()
{
	Impostor->Pos() = transform->Pos() + Vector3(0.0f,20.0f,0.0f);
	Impostor->Rot().y = CAM->GetParent()->Rot().y + XM_PI;
	Impostor->Update();

	//Vector2 dir = CAM->GlobalPos() - 
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
	if (transform->Active())
	{
		collider->Render();
	}
	else
	{
		blendState[1]->SetState();
		Impostor->Render();
		blendState[0]->SetState();
	}

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
