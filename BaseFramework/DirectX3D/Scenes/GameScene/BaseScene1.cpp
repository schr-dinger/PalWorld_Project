#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");

	//terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");
	//
	water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
	water->Pos() = { 250.0f,11.0f, 250.0f };
	water->Scale() *= 4.0f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveSpeed = 0.01f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveScale = 0.2f;

	//test
	palBox = new PalBox();


	player = new Player();
	player->SetTerrain(LandScapeManager::Get()->GetTerrain());

	PalsManager::Get()->SetTarget(player);
	PalsManager::Get()->SetPlayer(player);
	PalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	
	//PlayerPalsManager::Get()->SetTarget(); // �÷��̾�� �÷��̾ Ÿ���� Ÿ������ �����ϱ�
	PlayerPalsManager::Get()->SetPlayer(player);
	PlayerPalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());

	PalSpearManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());

}

BaseScene1::~BaseScene1()
{
	delete player;
	delete terrain;
	//delete terrainF;

	delete water;

	PalsManager::Get()->Delete();
	PlayerPalsManager::Get()->Delete();
	LandScapeManager::Get()->Delete();
}

void BaseScene1::Update()
{
	palBox->Place(player->GetFrontPoint()->GlobalPos().x, player->GetFrontPoint()->GlobalPos().z);




	water->Update();
	//tree->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	player->Update();

	palBox->Update();


	PalsManager::Get()->Update();
	PlayerPalsManager::Get()->Update();
	LandScapeManager::Get()->Update();
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

	palBox->PreRender();

}

void BaseScene1::Render()
{
	skyBox->Render();
	terrain->Render();
	water->Render();

	player->Render();
	
	palBox->Render();

	PalsManager::Get()->Render();
	PlayerPalsManager::Get()->Render();
	LandScapeManager::Get()->Render();
}

void BaseScene1::PostRender()
{
	PalsManager::Get()->PostRender();
	PlayerPalsManager::Get()->PostRender();
}

void BaseScene1::GUIRender()
{
	//player->GUIRender();
	water->GUIRender();
	//terrain->GUIRender();

	//palBox->GUIRender();

	PalsManager::Get()->GUIRender();

}
