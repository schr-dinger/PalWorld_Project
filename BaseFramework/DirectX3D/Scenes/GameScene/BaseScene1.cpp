#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH.png");
	terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");

	player = new Player();

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test2"); // �����信 ���� ī�޶� ��ġ ���� �ε� (������ �ε� ������ �״��)
	//CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)

	PalsManager::Get()->SetTarget(player);
	
}

BaseScene1::~BaseScene1()
{
	delete player;
	delete terrain;

	PalsManager::Get()->Delete();

}

void BaseScene1::Update()
{
	player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	player->Update();

	PalsManager::Get()->OnGround(terrainF); //��ǻƮ ��ŷ �ʿ�
	PalsManager::Get()->Update();

}

void BaseScene1::PreRender()
{
}

void BaseScene1::Render()
{
	skyBox->Render();

	terrain->Render();
	player->Render();
	
	PalsManager::Get()->Render();

}

void BaseScene1::PostRender()
{
	PalsManager::Get()->PostRender();

}

void BaseScene1::GUIRender()
{
	player->GUIRender();
	PalsManager::Get()->GUIRender();

}
