#include "Framework.h"

FieldUI::FieldUI()
{
	// 플레이어 체력 배고픔 바
	hpBar = new ProgressBar(
		L"Textures/Color/Red.png",
		L"Textures/Color/BlackGlass.png"
	);
	hpBar->SetTag("hp");
	hpBar->Scale().x = 0.75f;
	hpBar->Scale().y = 0.07f;

	hgyBar = new ProgressBar(
		L"Textures/Color/Green.png",
		L"Textures/Color/BlackGlass.png"
	);
	hgyBar->SetTag("hgy");
	hgyBar->Scale().x = 0.75f;
	hgyBar->Scale().y = 0.02f;
	// 그 왼쪽에 있는 체력, 배고픔 아이콘
	hpQuad  = new Quad(Vector2(1, 1));
	hpQuad->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_gauge_icon_HP.png");
	hpQuad->SetTag("hpQ");
	hpQuad->Scale().x = 20.0f;
	hpQuad->Scale().y = 20.0f;
	hpQuad->Pos() = {38.0f, 60.0f, 0.0f};

	hgyQuad = new Quad(Vector2(1, 1));
	hgyQuad->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_gauge_icon_hunger.png");
	hgyQuad->SetTag("hgyQ");
	hgyQuad->Scale().x = 20.0f;
	hgyQuad->Scale().y = 20.0f;
	hgyQuad->Pos() = { 38.0f, 39.0f, 0.0f };

	hpBar->Pos() = hpQuad->Pos() + Vector3(108, -0.5f, 0);
	hgyBar->Pos() = hgyQuad->Pos() + Vector3(108, -0.8f, 0);


	// 키 아이콘
	icon_1 = new Quad(Vector2(1, 1));
	icon_1->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_1.png");
	icon_1->SetTag("i1");
	icon_1->Scale().x = 20.0f;
	icon_1->Scale().y = 20.0f;
	icon_1->Pos() = { 38.0f, 160.0f, 0.0f };

	icon_2 = new Quad(Vector2(1, 1));
	icon_2->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_2.png");
	icon_2->SetTag("i2");
	icon_2->Scale().x = 20.0f;
	icon_2->Scale().y = 20.0f;

	icon_3 = new Quad(Vector2(1, 1));
	icon_3->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_3.png");
	icon_3->SetTag("i3");
	icon_3->Scale().x = 20.0f;
	icon_3->Scale().y = 20.0f;
	icon_3->Pos() = { 238.0f, 160.0f, 0.0f };

	icon_Q = new Quad(Vector2(1, 1));
	icon_Q->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_Q.png");
	icon_Q->SetTag("iQ");
	icon_Q->Scale().x = 20.0f;
	icon_Q->Scale().y = 20.0f;

	icon_E = new Quad(Vector2(1, 1));
	icon_E->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_E.png");
	icon_E->SetTag("iE");
	icon_E->Scale().x = 20.0f;
	icon_E->Scale().y = 20.0f;
	icon_E->Pos() = { 138.0f, 220.0f, 0.0f };

	icon_B = new Quad(Vector2(1, 1));
	icon_B->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_B.png");
	icon_B->SetTag("iB");
	icon_B->Scale().x = 20.0f;
	icon_B->Scale().y = 20.0f;

	// 팔 아이콘
	Pal1= new Quad(Vector2(1, 1));
	Pal2= new Quad(Vector2(1, 1));
	Pal3= new Quad(Vector2(1, 1));
	//Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTextureC());  // 테스트용
	//Pal2->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTextureC());
	//Pal3->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTextureC());
	Pal1->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	Pal2->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	Pal3->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	Pal1->Scale() = {80.0f, 80.0f, 0.0f};
	Pal2->Scale() = {30.0f, 30.0f, 0.0f};
	Pal3->Scale() = { 30.0f, 30.0f, 0.0f};
	Pal1->SetTag("P1");
	Pal2->SetTag("P2");
	Pal3->SetTag("P3");
	Pal1->Pos() = { 138.0f, 160.0f, 0.0f };
	Pal2->Pos() = { 73.0f, 160.0f, 0.0f };
	Pal3->Pos() = { 203.0f, 160.0f, 0.0f };

	// 팔 쿼드 아이콘
	PalQuad1 = new Quad(Vector2(1, 1));
	PalQuad2 = new Quad(Vector2(1, 1));
	PalQuad3 = new Quad(Vector2(1, 1));
	PalQuad1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50_C.png");
	PalQuad2->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50_C.png");
	PalQuad3->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50_C.png");
	PalQuad1->Scale() = { 80.0f, 80.0f, 0.0f };
	PalQuad2->Scale() = { 30.0f, 30.0f, 0.0f };
	PalQuad3->Scale() = { 30.0f, 30.0f, 0.0f };
	PalQuad1->SetTag("PQ1");
	PalQuad2->SetTag("PQ2");
	PalQuad3->SetTag("PQ3");
	PalQuad1->Pos() = { 138.0f, 160.0f, 0.0f };
	PalQuad2->Pos() = { 73.0f, 160.0f, 0.0f };
	PalQuad3->Pos() = { 203.0f, 160.0f, 0.0f };

	// 팔 선택
	selPal = 0;
	selPalQuad = new Quad(Vector2(1, 1));
	selPalQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	selPalQuad->Scale() = { 110.0f, 30.0f, 0.0f };
	selPalQuad->SetTag("SQ1");
	selPalQuad->Pos() = { 138.0f, 95.0f, 0.0f };

	selPalHpBar = new ProgressBar(
		L"Textures/Color/Red.png",
		L"Textures/Color/BlackGlass.png"
	);
	selPalHpBar->SetTag("Shp");
	selPalHpBar->Scale().x = 0.4f;
	selPalHpBar->Scale().y = 0.015f;
	selPalHpBar->Pos() = { 138.0f, 85.5f, 0.0f };


	// 폰트 포스
	HpFontPos = {61.0f, 69.0f};
	BuildFontPos = { 61.0f, 69.0f };
	selPalLvFontPos = { 88.0f, 102.0f };
	selPalLvNumFontPos = { 100.0f, 108.0f };
	selPalNameFontPos = { 127.0f, 106.0f };

	// 플레이어 팔 매니저에 따라 세팅
	SetPalUI();

	// 폰트 테스트용
	fontPos = {};
	maxHp = 500;
	curHp = 500;
}

FieldUI::~FieldUI()
{
	delete hpBar;
	delete hgyBar;
	delete hpQuad;
	delete hgyQuad;
	delete icon_1;
	delete icon_2;
	delete icon_3;
	delete icon_Q;
	delete icon_E;
	delete icon_B;

	delete Pal1;
	delete Pal2;
	delete Pal3;
	delete PalQuad1;
	delete PalQuad2;
	delete PalQuad3;
	delete selPalQuad;
	delete selPalHpBar;
}	

void FieldUI::Update()
{
	// 팔 선택
	if (KEY_DOWN('E')) // 선택 팰 소환
	{
		if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
		{
			PlayerPalsManager::Get()->SetSelPal(selPal);
			PlayerPalsManager::Get()->Summons();
		}
	}
	else if (KEY_DOWN('3')) // 오른쪽 팰 선택
	{
		selPal++;
		SetPalUI();
	}
	else if (KEY_DOWN('1')) // 왼쪽 팔 선택
	{
		selPal--;
		SetPalUI();
	}
	hpBar  ->Update();
	hpBar  ->SetAmount(curHp / (float)maxHp);
	hgyBar ->Update();
	hgyBar ->SetAmount(curHp / (float)maxHp);
	hpQuad ->Update();
	hgyQuad->Update();
	icon_1 ->Update();
	icon_2 ->Update();
	icon_3 ->Update();
	icon_Q ->Update();
	icon_E ->Update();
	icon_B ->Update();
	Pal1->Update();
	Pal2->Update();
	Pal3->Update();
	PalQuad1->Update();
	PalQuad2->Update();
	PalQuad3->Update();
	selPalQuad->Update();
	selPalHpBar->Update();
}

void FieldUI::PostRender()
{
	hpBar->Render();
	hgyBar->Render();
	hpQuad->Render();
	hgyQuad->Render();
	icon_1->Render();
	icon_2->Render();
	icon_3->Render();
	icon_Q->Render();
	icon_E->Render();
	icon_B->Render();
	PalQuad1->Render();
	PalQuad2->Render();
	PalQuad3->Render();
	Pal1->Render();
	Pal2->Render();
	Pal3->Render();

	
	//체력 폰트
	{
		// 체력
		string tmpString = to_string(curHp) + " / " + to_string(maxHp);
		//tmpString = "99";
		Font::Get()->SetStyle("HpUI");
		Font::Get()->RenderText(tmpString, { HpFontPos.x, HpFontPos.y });

		if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr) // 선택 있을 시 쿼드, 레벨, 이름 랜더
		{
			selPalQuad->Render();
			selPalHpBar->Render();
			selPalHpBar->SetAmount(PlayerPalsManager::Get()->GetPal(selPal)->GetCurHp());

			tmpString = to_string(PlayerPalsManager::Get()->GetPal(selPal)->level);
			//tmpString = "99";
			Font::Get()->SetStyle("FieldLvNum");
			Font::Get()->RenderText(tmpString, { selPalLvNumFontPos.x, selPalLvNumFontPos.y });

			tmpString = "LV";
			Font::Get()->SetStyle("FieldLv");
			Font::Get()->RenderText(tmpString, { selPalLvFontPos.x, selPalLvFontPos.y });
			tmpString = PlayerPalsManager::Get()->GetPal(selPal)->name;
			Font::Get()->SetStyle("FieldName");
			Font::Get()->RenderText(tmpString, { selPalNameFontPos.x, selPalNameFontPos.y });

		}
		
		Font::Get()->SetStyle("Default");
		Font::Get()->GetDC()->EndDraw();
		Font::Get()->GetDC()->BeginDraw();
	}

	
}

void FieldUI::GUIRender()
{
	ImGui::SliderFloat("FontPosX", &fontPos.x, 0, 1280);
	ImGui::SliderFloat("FontPosY", &fontPos.y, 0, 720);

	
	//ImGui::SliderInt("CurHp: %d", &curHp, 0, maxHp);
	//icon_2->GUIRender();
	//icon_Q->GUIRender();
	//icon_B->GUIRender();


}

void FieldUI::SetPalUI()
{
	if (selPal < 0)
	{
		selPal = 4;
	}
	else if (selPal > 4)
	{
		selPal = 0;
	}
	// 없는 건 없는데로 출력하기
	//if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
	//{
	//	Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(selPal)->GetTextureC());
	//}
	//else
	//{
	//	Pal1->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}
	//int tmp1 = (selPal + 1) % 5; // 오른쪽은 다음에 있는 팔
	//if (PlayerPalsManager::Get()->GetPal(tmp1) != nullptr)
	//{
	//	Pal3->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(tmp1)->GetTextureC());
	//}
	//else
	//{
	//	Pal3->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}
	//int tmp2 = (selPal + 4) % 5; // 왼쪽은 전에 있는 팔
	//if (PlayerPalsManager::Get()->GetPal(tmp2) != nullptr)
	//{
	//	Pal2->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(tmp2)->GetTextureC());
	//}
	//else
	//{
	//	Pal2->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}


	// 게임처럼 세팅 테스트
	int test[3] = {-1, -1, -1};
	int tmp = 0;

	if (KEY_DOWN('1')) // 왼쪽 팔 선택
	{
		int tmpSel = selPal;
		FOR(5)
		{
			if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
			{
				test[tmp] = selPal;
				if (tmp == 0)
				{
					selPal = tmpSel;
				}
				tmp++;
				if (tmp >= 3)
				{
					tmp = 2;
				}
			}
			if (tmp == 0)
			{
				selPal--;
				if (selPal < 0)
				{
					selPal = 4;
				}
			}
			else
			{
				selPal++;
				selPal %= 5;
			}
			
		}
	}
	else
	{
		FOR(5)
		{
			if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
			{
				test[tmp] = selPal;
				tmp++;
				if (tmp >= 3)
				{
					tmp = 2;
				}
			}
			selPal++;
			selPal %= 5;
		}
	}

	
	if (test[0] != -1)
	{
		Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(test[0])->GetTextureC());
		selPal = test[0];
	}
	else
	{
		Pal1->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");

	}
	if (test[1] != -1)
	{
		Pal3->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(test[1])->GetTextureC());

	}
	else
	{
		Pal3->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");

	}
	if (test[2] != -1)
	{
		Pal2->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(test[2])->GetTextureC());

	}
	else
	{
		Pal2->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");

	}


}
