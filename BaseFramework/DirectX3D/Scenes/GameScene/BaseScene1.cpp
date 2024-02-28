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


	player = new Player();
	player->SetTerrain(terrainF);

	player->Scale() *= 2.0f;
	
		
	//CAM->SetTarget(player);
	//CAM->TargetOptionLoad("test3");

	//CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)

	PalsManager::Get()->SetTarget(player);
	PalsManager::Get()->SetTerrain(terrainF);
	
}

BaseScene1::~BaseScene1()
{
	delete player;
	delete terrain;
	delete terrainF;

	delete water;
	delete tree;
	delete grass;

	PalsManager::Get()->Delete();

}

void BaseScene1::Update()
{
	water->Update();
	tree->Update();
	grass->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	player->Update();

	//PalsManager::Get()->OnGround(terrainF); 
	PalsManager::Get()->Update();

	
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
	//skyBox->Render();

	terrain->Render();
	//water->Render();
	//grass->Render();
	//rock->Render();


	//tree->Render();

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
	//water->GUIRender();
	terrain->GUIRender();

	//PalsManager::Get()->GUIRender();

	 //player->GetModel()->GUIRender();

}
