#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH.png");
	//terrain = new Terrain();

	player = new Player();

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test2"); // 나루토에 맞춘 카메라 위치 설정 로드 (있으면 로드 없으면 그대로)
	//CAM->LookAtTarget(); // 팔로우캠 + 추적 대상 있음 + 그 추적 대상을 락온으로 추적 (이 경우는 나루토)


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
