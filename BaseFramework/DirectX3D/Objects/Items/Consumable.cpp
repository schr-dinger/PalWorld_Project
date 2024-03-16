#include "Framework.h"
#include "Consumable.h"

Consumable::Consumable(int num)
{

	this->num = num;
	type = CONSUMABLE;

	//transform = new Transform();

	//collider = new CapsuleCollider(3);
	//collider->Scale() *= 2.0f;
	//collider->SetParent(transform);

	//transform->UpdateWorld();

	switch (num)
	{
	case 1:
		icon = Texture::Add(L"Textures/UI/Inv/T_Sphere.png");
		break;
	case 2:
		icon = Texture::Add(L"Textures/UI/Inv/T_Arrow.png");
		break;
	case 3:
		icon = Texture::Add(L"Textures/UI/Inv/T_Bullet.png");
		break;
	default:
		icon = Texture::Add(L"Textures/Color/White.png");
		break;

	}


}


Consumable::~Consumable()
{
	//delete collider;
	//delete transform;

}

void Consumable::Update()
{

	//collider->UpdateWorld();
}

void Consumable::Render()
{
	//collider->Render();
}

