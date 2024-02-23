#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH.png");
	terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");

	player = new Player();

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test2"); // 나루토에 맞춘 카메라 위치 설정 로드 (있으면 로드 없으면 그대로)
	//CAM->LookAtTarget(); // 팔로우캠 + 추적 대상 있음 + 그 추적 대상을 락온으로 추적 (이 경우는 나루토)

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

	PalsManager::Get()->OnGround(terrainF); //컴퓨트 피킹 필요
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
