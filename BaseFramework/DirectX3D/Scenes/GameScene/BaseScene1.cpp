#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	//Let there be light
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


	PalsManager::Get()->SetTarget(PlayerManager::Get()->GetPlayer());
	PalsManager::Get()->SetPlayer(PlayerManager::Get()->GetPlayer());
	PalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());
	
	//PlayerPalsManager::Get()->SetTarget(); // 플레이어에서 플레이어가 타겟한 타겟으로 설정하기
	PlayerPalsManager::Get()->SetPlayer(PlayerManager::Get()->GetPlayer());
	PlayerPalsManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());

	PalSpearManager::Get()->SetTerrain(LandScapeManager::Get()->GetTerrain());

	FieldPalSkillManager::Get(); // 생성자용
	MyPalSkillManager::Get();	 // 생성자용

	//palBoxUi = new PalBoxUi();

	// 스킬 테스트
	//testSkill = new Tornado();

	// UI테스트
	//testUI = new FieldUI();

	// 모델 테스트
	//mam = new ModelAnimator("Mammoth");
	//mam->ReadClip("Idle");
	//mam->ReadClip("Walk");
	//mam->ReadClip("Run");
	//mam->ReadClip("Attack");
	//
	//mam->Scale() *= 0.01f;

}

BaseScene1::~BaseScene1()
{
	//delete player;
	//delete terrain;
	//delete terrainF;
	delete shadow;
	delete water;

	PalsManager::Get()->Delete();
	PlayerPalsManager::Get()->Delete();
	LandScapeManager::Get()->Delete();
	PlayerManager::Get()->Delete();
	UiManager::Get()->Delete();
	StructureManager::Get()->Delete();
	//delete palBoxUi;
}

void BaseScene1::Update()
{
	LightBuffer::Light* light1 = Environment::Get()->GetLight(1);
	light1->pos = CAM->GlobalPos();

	UiManager::Get()->Update(); // UI 관련 업데이트가 먼저



	water->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	//player->Update();
	PlayerManager::Get()->Update();

	StructureManager::Get()->Update();


	PalsManager::Get()->Update();
	PlayerPalsManager::Get()->Update();
	LandScapeManager::Get()->Update();
	//PlayerManager::Get()->Update();
	FieldPalSkillManager::Get()->Update(); // 벡터 터짐 방지
	MyPalSkillManager::Get()->Update();	   //  -> 맨 마지막에 업데이트

	// UI테스트
	//testUI->Update();
	//mam->Update();
}

void BaseScene1::PreRender()
{
	//PalSpearManager::Get()->PreRender();

	water->SetRefraction();

	// 일렁인 쪽 클래스의 쿼드에 일렁임의 결과 출력
	skyBox->Render();

	// 반사
	water->SetReflection();
	// 반사 출력
	skyBox->Render();

	StructureManager::Get()->PreRender();
	//LandScapeManager::Get()->PreRender();

}

void BaseScene1::Render()
{

	skyBox->Render();
	//terrain->Render();
	water->Render();
	
	//mam->Render();

	StructureManager::Get()->Render();
	PlayerManager::Get()->Render();

	PalsManager::Get()->Render();
	PlayerPalsManager::Get()->Render();

	LandScapeManager::Get()->Render();
	AStarManager::Get()->Render();
}

void BaseScene1::PostRender()
{
	//PalSpearManager::Get()->PostRender();


	PalsManager::Get()->PostRender();
	PlayerPalsManager::Get()->PostRender();
	StructureManager::Get()->PostRender();

	// UI테스트
	//testUI->PostRender();
	UiManager::Get()->PostRender();

}

void BaseScene1::GUIRender()
{
	//PlayerManager::Get()->GUIRender();

	//water->GUIRender();
	//terrain->GUIRender();
	//palBox->GUIRender();

	//PalsManager::Get()->GUIRender();
	PlayerPalsManager::Get()->GUIRender();

	//PlayerManager::Get()->GUIRender();
	//PalSpearManager::Get()->GUIRender();

	// UI테스트
	//testUI->GUIRender();
	UiManager::Get()->GuiRender();
	//LandScapeManager::Get()->GUIRender();
}

void BaseScene1::SetLights()
{
	LightBuffer::Light* light0 = Environment::Get()->GetLight(0);
	light0->type = 0;
	light0->range = 3000.0f;
	light0->color = { 55.0f / 255.0f,55.0f / 255.0f,55.0f / 255.0f ,0 };
	light0->direction = { 0,-1,0 };
	light0->pos = { 0.01f,300.0f,0.01f };

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
