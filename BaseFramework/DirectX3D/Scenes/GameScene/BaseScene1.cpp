#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");
	terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");
	//
	water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
	water->Pos() = { 0.0f,10.0f,0.0f };
	water->GetRefraction()->GetWaterBuffer()->Get().waveSpeed = 0.01f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveScale = 0.2f;

	tree = new Tree(terrainF);
	grass = new Grass(terrainF);
	rock = new Rock(terrainF);

	player = new Player();
	player->SetTerrain(terrainF);

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test3");
	//CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)

	PalsManager::Get()->SetTarget(player);
	PalsManager::Get()->SetPlayer(player);
	PalsManager::Get()->SetTerrain(terrainF);
	
	//PlayerPalsManager::Get()->SetTarget(); // �÷��̾�� �÷��̾ Ÿ���� Ÿ������ �����ϱ�
	PlayerPalsManager::Get()->SetPlayer(player);
	PlayerPalsManager::Get()->SetTerrain(terrainF);
}

BaseScene1::~BaseScene1()
{
	delete player;
	delete terrain;
	delete terrainF;

	delete water;
	delete tree;
	delete grass;
	delete rock;

	PalsManager::Get()->Delete();
	PlayerPalsManager::Get()->Delete();

}

void BaseScene1::Update()
{
	water->Update();
	tree->Update();
	grass->Update();
	rock->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	player->Update();

	PalsManager::Get()->Update();
	PlayerPalsManager::Get()->Update();

}

void BaseScene1::PreRender()
{
	water->SetRefraction();

	//�Ϸ��� �� Ŭ������ ���忡 �Ϸ����� ��� ���
	skyBox->Render();

	//�ݻ�
	water->SetReflection();
	//�ݻ� ���
	skyBox->Render();

}

void BaseScene1::Render()
{
	skyBox->Render();
	terrain->Render();
	water->Render();
	grass->Render();
	rock->Render();

	tree->Render();

	player->Render();
	
	PalsManager::Get()->Render();
	PlayerPalsManager::Get()->Render();

}

void BaseScene1::PostRender()
{
	PalsManager::Get()->PostRender();
	PlayerPalsManager::Get()->PostRender();

}

void BaseScene1::GUIRender()
{
	player->GUIRender();
	//water->GUIRender();
	terrain->GUIRender();

	PalsManager::Get()->GUIRender();

}
