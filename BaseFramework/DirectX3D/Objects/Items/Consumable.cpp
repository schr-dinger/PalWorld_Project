#include "Framework.h"
#include "Consumable.h"

Consumable::Consumable(int num)
{

	this->num = num;
	type = CONSUMABLE;


	switch (this->num)
	{
	case 1:
		icon = Texture::Add(L"Textures/UI/Inv/T_Sphere.png");
		MakeTime = 40;
		break;
	case 2:
		icon = Texture::Add(L"Textures/UI/Inv/T_Bullet.png");
		MakeTime = 30;
		break;
	case 3:
		icon = Texture::Add(L"Textures/UI/Inv/T_Arrow.png");
		MakeTime = 30;
		break;
	default:
		icon = Texture::Add(L"Textures/Color/White.png");
		break;

	}


}


Consumable::~Consumable()
{
	
	delete test;
	
}

void Consumable::Update()
{
		
}

void Consumable::Render()
{

}

