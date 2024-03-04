#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");
	//terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");
	//
	water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
	water->Pos() = { 0.0f,10.0f,0.0f };
	water->GetRefraction()->GetWaterBuffer()->Get().waveSpeed = 0.01f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveScale = 0.2f;

	//test
	palBox = new PalBox();


	player = new Player();
	player->SetTerrain(LandScapeManager::Get()->GetTerrain());

	//CAM->LookAtTarget(); // 팔로우캠 + 추적 대상 있음 + 그 추적 대상을 락온으로 추적 (이 경우는 나루토)

	PalsManager::Get()->SetTarget(player);
	PalsManager::Get()->SetPlayer(player);
	PalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	
	//PlayerPalsManager::Get()->SetTarget(); // 플레이어에서 플레이어가 타겟한 타겟으로 설정하기
	PlayerPalsManager::Get()->SetPlayer(player);
	PlayerPalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());

<<<<<<< HEAD
	// 스킬 테스트
	testSkill = new Tornado();
=======
	PalSpearManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
>>>>>>> main

	FieldPalSkillManager::Get(); // 생성자 만들기
	MyPalSkillManager::Get();	 // 생성자 만들기
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
<<<<<<< HEAD

	FieldPalSkillManager::Get()->Update(); // 다른 업데이트가 다 돈 후 마지막에 스킬 업데이트하기
	                                       // 벡터 터짐 방지
	MyPalSkillManager::Get()->Update();
=======
	LandScapeManager::Get()->Update();
>>>>>>> main
}

void BaseScene1::PreRender()
{
	water->SetRefraction();

	//일렁임 쪽 클래스의 쿼드에 일렁임의 결과 출력
	skyBox->Render();

	//반사
	water->SetReflection();
	//반사 출력
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
<<<<<<< HEAD


=======
	LandScapeManager::Get()->Render();
>>>>>>> main
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
<<<<<<< HEAD
	//terrain->GUIRender();
	//
	//ice->GUIRender();
	//
	//PalsManager::Get()->GUIRender();
=======
	terrain->GUIRender();

	palBox->GUIRender();

	PalsManager::Get()->GUIRender();
>>>>>>> main

}
