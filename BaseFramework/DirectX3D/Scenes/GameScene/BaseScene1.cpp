#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH.png");
	//terrain = new Terrain();

	player = new Player();

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test2"); // �����信 ���� ī�޶� ��ġ ���� �ε� (������ �ε� ������ �״��)
	//CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)


	penguin = new Penguin();
	penguin->Scale() *= 0.01f;
}

BaseScene1::~BaseScene1()
{
}

void BaseScene1::Update()
{
	//player->Jump(terrain->GetHeight(player->GlobalPos()));
	player->Jump(70);

	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	player->Update();
	penguin->Update();
}

void BaseScene1::PreRender()
{
}

void BaseScene1::Render()
{
	terrain->Render();
	player->Render();
	penguin->Render();
}

void BaseScene1::PostRender()
{
}

void BaseScene1::GUIRender()
{
	player->GUIRender();
	penguin->GUIRender();
	terrain->GUIRender();
}
