#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	//terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");

	//
	SetLights();

	shadow = new Shadow();


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
	//delete terrain;
	//delete terrainF;
	delete shadow;
	delete water;

	PalsManager::Get()->Delete();
	PlayerPalsManager::Get()->Delete();
	LandScapeManager::Get()->Delete();
}

void BaseScene1::Update()
{
	LightBuffer::Light* light1 = Environment::Get()->GetLight(1);
	light1->pos = CAM->GlobalPos();

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

	//LandScapeManager::Get()->PreRender();
}

void BaseScene1::Render()
{
	skyBox->Render();
	//terrain->Render();
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
	//water->GUIRender();
	//terrain->GUIRender();

	//palBox->GUIRender();

	PalsManager::Get()->GUIRender();

}

void BaseScene1::SetLights()
{
	LightBuffer::Light* light0 = Environment::Get()->GetLight(0);
	light0->type = 0;
	light0->range = 3000.0f;
	light0->color = { 55.0f / 255.0f,55.0f / 255.0f,55.0f / 255.0f ,0 };
	light0->direction = { 0,-1,0 };

	LightBuffer::Light* light1 = Environment::Get()->AddLight();
	light1->type = 1;
	light1->range = 3000.0f;
	light1->color = { 150.0f / 255.0f,150.0f / 255.0f,150.0f / 255.0f ,0 };
	light1->direction = { 0,-1,0 };


	LightBuffer::Light* light2 = Environment::Get()->AddLight();
	light2->type = 1;
	light2->range = 0.01f;
	light2->active = 0;

	LightBuffer::Light* light3 = Environment::Get()->AddLight();
	light3->type = 1;
	light3->range = 0.01f;
	light3->active = 0;
}
