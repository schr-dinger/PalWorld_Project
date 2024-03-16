#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	//Let there be light
	SetLights();

	// 그림자용 모델
	SetShadowModel();

	shadow = new Shadow(16384, 16384); // 픽셀 깨짐 최소화
	//shadow = new Shadow();


	//terrainF = new Terrain();
	skyBox = new SkyBox(L"Textures/Landscape/testsky.dds");
	//
	water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
	water->Pos() = { 250.0f,11.0f, 250.0f };
	water->Scale() *= 4.0f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveSpeed = 0.01f;
	water->GetRefraction()->GetWaterBuffer()->Get().waveScale = 0.2f;


	//PalsManager::Get()->SetTarget(PlayerManager::Get()->GetPlayer());
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
	delete ModelP;
	delete ModelM;
	delete ModelD;

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

	StructureManager::Get()->Update();
	UiManager::Get()->Update(); // UI 관련 업데이트가 먼저



	water->Update();
	//player->Jump(terrainF->GetHeight(player->GlobalPos()));
	//if (KEY_DOWN(VK_SPACE)) player->GlobalPos().y = terrain->GetHeight(player->GlobalPos());
	//player->Update();
	ItemManager::Get()->Update();
	PlayerManager::Get()->Update();



	PalsManager::Get()->Update();
	PlayerPalsManager::Get()->Update();
	LandScapeManager::Get()->Update();
	//PlayerManager::Get()->Update();
	FieldPalSkillManager::Get()->Update(); // 벡터 터짐 방지
	MyPalSkillManager::Get()->Update();	   //  -> 맨 마지막에 업데이트

	// UI테스트
	//testUI->Update();
	//mam->Pos() = CAM->ScreenToWorld(mousePos);
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

	// 그림자
	//shadow->SetRenderTargetPos(PlayerManager::Get()->GetPlayer()->GlobalPos());
	shadow->SetRenderTargetPos(CAM->GlobalPos());
	PlayerManager::Get()->GetPlayer()->ShadowRender();
	//PalsManager::Get()->ShadowRender();
	//PlayerPalsManager::Get()->ShadowRender();
	RenderShadowModel();
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

	// 그림자 + 터레인
	shadow->SetRender();
	LandScapeManager::Get()->Render();
	//AStarManager::Get()->Render();
	UiManager::Get()->Render();

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

	PlayerManager::Get()->GUIRender();
	//PalSpearManager::Get()->GUIRender();

	// UI테스트
	//testUI->GUIRender();
	UiManager::Get()->GuiRender();
	//LandScapeManager::Get()->GUIRender();
	//ImGui::Text("Wold X : %f", CAM->ScreenToWorld(mousePos).x);
	//ImGui::Text("Wold Y : %f", CAM->ScreenToWorld(mousePos).y);
	//ImGui::Text("Wold Z : %f", CAM->ScreenToWorld(mousePos).z);
	//mam->GUIRender();
}

void BaseScene1::SetLights()
{
	LightBuffer::Light* light0 = Environment::Get()->GetLight(0);
	light0->type = 0;
	light0->range = 3000.0f;
	//light0->color = { 55.0f / 255.0f,55.0f / 255.0f,55.0f / 255.0f ,0 };
	light0->color = { 1.0f,1.0f,1.0f ,0 };
	//light0->direction = { 0,-1,0 };
	light0->direction = { 0.5f,-1.0f,0.5f };
	light0->pos = { 0.01f,300.0f,0.01f };

	//LightBuffer::Light* light1 = Environment::Get()->AddLight();
	//light1->type = 1;
	//light1->range = 3000.0f;
	//light1->color = { 150.0f / 255.0f,150.0f / 255.0f,150.0f / 255.0f ,0 };
	//light1->direction = { 0,-1,0 };
	//
	//
	LightBuffer::Light* light1 = Environment::Get()->AddLight();
	light1->type = 1;
	light1->range = 0.01f;
	light1->active = 1;
	
	LightBuffer::Light* light2 = Environment::Get()->AddLight();
	light2->type = 1;
	light2->range = 0.01f;
	light2->active = 1;
}

void BaseScene1::SetShadowModel()
{
	ModelP = new ModelAnimatorInstancing("PenGuin");
	ModelP->ReadClip("Idle");
	ModelP->ReadClip("Walk");
	ModelP->ReadClip("Run");
	ModelP->ReadClip("Attack");
	ModelP->ReadClip("Damage");
	ModelP->ReadClip("Work");
	ModelP->SetTag("Penguin");
	ModelP->SetShader(L"Light/DepthMap.hlsl");
	ModelP->Scale() *= 0.01f;


	ModelM = new ModelAnimatorInstancing("Mammoth");
	ModelM->ReadClip("Idle");
	ModelM->ReadClip("Walk");
	ModelM->ReadClip("Run");
	ModelM->ReadClip("Attack");
	ModelM->ReadClip("Damage");
	ModelM->SetTag("mammoth");
	ModelM->SetShader(L"Light/DepthMap.hlsl");
	ModelM->Scale() *= 0.01f;

	ModelD = new ModelAnimatorInstancing("DarkWolf");
	ModelD->ReadClip("Idle");
	ModelD->ReadClip("Walk");
	ModelD->ReadClip("Run");
	ModelD->ReadClip("Attack");
	ModelD->ReadClip("Damage");
	ModelD->SetTag("wolf");
	ModelD->SetShader(L"Light/DepthMap.hlsl");
	ModelD->Scale() *= 0.01f;

}

void BaseScene1::RenderShadowModel()
{
	// 필드 팰즈 매니저
	for (int i = 0; i < PalsManager::Get()->GetPalsInstancing().size(); i++)
	{
		int tmpIII = 0;
		for (Transform* pal : PalsManager::Get()->GetPalsInstancing()[i]->GetInstancingTransform())
		{
			if (pal->Active())
			{
				if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "PenGuin")
				{
					ModelP->Pos() = pal->Pos();
					ModelP->Rot() = pal->Rot();
					//ModelP->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelP->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelP->UpdateWorld();
					ModelP->Render();
				}
				else if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "Mammoth")
				{
					ModelM->Pos() = pal->Pos();
					ModelM->Rot() = pal->Rot();
					//ModelM->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelM->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelM->UpdateWorld();
					ModelM->Render();
				}
				else if (PalsManager::Get()->GetPalsInstancing()[i]->ModelName == "DarkWolf")
				{
					ModelD->Pos() = pal->Pos();
					ModelD->Rot() = pal->Rot();
					//ModelD->GetFrameB()->Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelD->GetFrameB().Get().cur = PalsManager::Get()->GetPalsInstancing()[i]->GetFrameIB().Get().motions[tmpIII].cur;

					ModelD->UpdateWorld();
					ModelD->Render();
				}
			}
			tmpIII++;
		}
	}

	// 플레이어 팰즈 매니저
	for (auto iter = PlayerPalsManager::Get()->GetPalsMAI().begin(); iter != PlayerPalsManager::Get()->GetPalsMAI().end(); iter++)
	{
		int tmpIII = 0;
		for (Transform* pal : iter->second->GetInstancingTransform())
		{
			if (pal->Active())
			{
				if (iter->second->ModelName == "PenGuin")
				{
					ModelP->Pos() = pal->Pos();
					ModelP->Rot() = pal->Rot();
					//ModelP->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelP->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelP->UpdateWorld();
					ModelP->Render();
				}
				else if (iter->second->ModelName == "Mammoth")
				{
					ModelM->Pos() = pal->Pos();
					ModelM->Rot() = pal->Rot();
					//ModelM->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelM->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelM->UpdateWorld();
					ModelM->Render();
				}
				else if (iter->second->ModelName == "DarkWolf")
				{
					ModelD->Pos() = pal->Pos();
					ModelD->Rot() = pal->Rot();
					//ModelD->GetFrameB()->Get().cur = iter->second->GetFrameIB()->Get().motions[tmpIII].cur;
					ModelD->GetFrameB().Get().cur = iter->second->GetFrameIB().Get().motions[tmpIII].cur;

					ModelD->UpdateWorld();
					ModelD->Render();
				}
			}
			tmpIII++;
		}
	}
}
