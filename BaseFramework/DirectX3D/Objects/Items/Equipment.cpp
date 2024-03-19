#include "Framework.h"

Equipment::Equipment(int num)
{

	this->num = num;
	type = WEAPON;

	switch (num)
	{
	case 1:
		test = new Model("Rifle");
		icon = Texture::Add(L"Textures/UI/Inv/T_Rifle.png");
		//name = "라이플";

		test->Scale() *= 0.8f;
		test->Rot().x += XM_PIDIV2;
		test->Rot().y -= 0.02f;

		break;
	case 2:
		test = new Model("Rifle");
		icon = Texture::Add(L"Textures/UI/Inv/T_Bow.png");

		test->Rot().x -= XM_PIDIV4 + XM_PIDIV4 - (XM_PIDIV4 * 10 / XM_PIDIV4);
			test->Rot().y += XM_PIDIV4;

		//name = "활";

		test->Rot().x -= XM_PIDIV2;
		break;
	case 3:
		test = new Model("PickExe");
		icon = Texture::Add(L"Textures/UI/Inv/T_Pick.png");

		test->Rot().x += XM_PIDIV2;
		test->Rot().y -= XM_PIDIV4 + XM_PIDIV2;
		//test->Rot().x -= XM_PIDIV2;
		break;
	default:

		break;
	}

	// collider = new SphereCollider();
	// collider->setparent(transform);



}

Equipment::~Equipment()
{
	delete test;
	delete collider;
	delete transform;

}

void Equipment::Update()
{

	// test->UpdateWorld();

}

void Equipment::Render()
{
	// test->Render();

}


