#include "Framework.h"
#include "ingredient.h"

Ingredient::Ingredient(int num)
{

	this->num = num;
	type = INGREDIENT;

	//transform = new Transform();

	collider = new CapsuleCollider(3);
	collider->Scale() *= 2.0f;
	//collider->SetParent(transform);

	//transform->UpdateWorld();

	switch (num)
	{
	case 1:
		icon = Texture::Add(L"Textures/UI/Inv/T_Wood.png");
		break;
	case 2:
		icon = Texture::Add(L"Textures/UI/Inv/T_Stone.png");
		break;
	default:
		icon = Texture::Add(L"Textures/Color/White.png");

	}



}


Ingredient::~Ingredient()
{
	delete test;
	delete transform;
	delete collider;
}

void Ingredient::Update()
{

	collider->UpdateWorld();
}

void Ingredient::Render()
{
	collider->Render();
}

/*
void Ingredient::SetActive()
{
	transform->SetActive(false);

}
*/
/*
bool Ingredient::isColPlayer()
{

	if (collider->IsCollision(PlayerManager::Get()->GetPlayer()->GetPlayerCol()))
	{
		Item* test = new Ingredient(num);

		ItemManager::Get()->Mining(test);

		transform->SetActive(false);
		return false;
	}


	return true;

	// itemManager:: ½Àµæ

}
*/