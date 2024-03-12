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
	icon_2->Pos() = { 1023.0f, 26.0f, 0.0f };

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
	icon_Q->Pos() = { 1235.0f, 146.0f, 0.0f };

	icon_E = new Quad(Vector2(1, 1));
	icon_E->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_E.png");
	icon_E->SetTag("iE");
	icon_E->Scale().x = 20.0f;
	icon_E->Scale().y = 20.0f;
	icon_E->Pos() = { 138.0f, 220.0f, 0.0f };

	icon_E2 = new Quad(Vector2(1, 1));
	icon_E2->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_E.png");
	icon_E2->SetTag("iE");
	icon_E2->Scale().x = 20.0f;
	icon_E2->Scale().y = 20.0f;
	icon_E2->Pos() = { 1235.0f, 172.0f, 0.0f };

	icon_B = new Quad(Vector2(1, 1));
	icon_B->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_B.png");
	icon_B->SetTag("iB");
	icon_B->Scale().x = 20.0f;
	icon_B->Scale().y = 20.0f;
	icon_B->Pos() = { 1235.0f, 198.0f, 0.0f };

	icon_MW = new Quad(Vector2(1, 1));
	icon_MW->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_MenuKeyGuide_MouseWheelAxis.png");
	icon_MW->SetTag("iCB");
	icon_MW->Scale().x = 25.0f;
	icon_MW->Scale().y = 25.0f;
	icon_MW->Pos() = { 1161.0f, 26.0f, 0.0f };

	icon_Swap1 = new Quad(Vector2(1, 1));
	icon_Swap1->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_KeyGuide_change.png");
	icon_Swap1->SetTag("iSwap");
	icon_Swap1->Scale().x = 25.0f;
	icon_Swap1->Scale().y = 25.0f;
	icon_Swap1->Pos() = { 1045.0f, 26.0f, 0.0f };
	icon_Swap2 = new Quad(Vector2(1, 1));
	icon_Swap2->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_KeyGuide_change.png");
	icon_Swap2->SetTag("iSwap");
	icon_Swap2->Scale().x = 25.0f;
	icon_Swap2->Scale().y = 25.0f;
	icon_Swap2->Pos() = { 1183.0f, 26.0f, 0.0f };

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
	PalQuad1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20_C.png");
	PalQuad2->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20_C.png");
	PalQuad3->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20_C.png");
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
	selPalQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
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

	// 플레이어 장비
	// 팰스피어
	palSpearTextQuad = new Quad(Vector2(1, 1));
	palSpearRenderQuad = new Quad(Vector2(1, 1));
	palSpearIcon = new Quad(Vector2(1, 1));
	palSpearTextQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	palSpearRenderQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	palSpearIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_palsphere_0.png");
	palSpearTextQuad->  SetTag("PT");
	palSpearRenderQuad->SetTag("PR");
	palSpearIcon->      SetTag("PI");
	palSpearTextQuad->Pos() = { 1034.0f, 108.0f, 0.0f };
	palSpearRenderQuad->Pos() = { 1034.0f, 68.0f, 0.0f };
	palSpearIcon->Pos() = { 1006.0f, 68.0f, 0.0f };
	palSpearTextQuad->  Scale() = { 110.0f, 23.0f, 0.0f };
	palSpearRenderQuad->Scale() = { 110.0f, 50.8f, 0.0f };
	palSpearIcon->      Scale() = { 40.0f, 40.0f, 0.0f };
	// 장비(활, 총, 도끼...)
	equipTextQuad = new Quad(Vector2(1, 1));
	equipRenderQuad = new Quad(Vector2(1, 1));
	equipIcon = new Quad(Vector2(1, 1));
	equipSlash = new Quad(Vector2(1, 1));
	equipTextQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	equipRenderQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	equipIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_Bow_UI.png");
	equipSlash->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
	equipTextQuad->SetTag("ET");
	equipRenderQuad->SetTag("ER");
	equipIcon->SetTag("EI");
	equipSlash->SetTag("ES");
	equipTextQuad->Pos() = { 1172.0f, 108.0f, 0.0f };
	equipRenderQuad->Pos() = { 1172.0f, 68.0f, 0.0f };
	equipIcon->Pos() = { 1144.0f, 68.0f, 0.0f };
	equipSlash->Pos() = { 1196.0f, 68.0f, 0.0f };
	equipTextQuad->  Scale() = { 160.0f, 23.0f, 0.0f };
	equipRenderQuad->Scale() = { 160.0f, 50.8f, 0.0f };
	equipIcon->      Scale() = { 100.0f, 50.0f, 0.0f };
	equipSlash->     Scale() = { 1.0f, 38.0f, 0.0f };

	// 플레이 수행
	pressBQuad = new Quad(Vector2(1, 1));
	pressEQuad = new Quad(Vector2(1, 1));
	pressQQuad = new Quad(Vector2(1, 1));
	pressBQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	pressEQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	pressQQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	pressBQuad->SetTag("BQ");
	pressEQuad->SetTag("EQ");
	pressQQuad->SetTag("QQ");
	pressBQuad->Pos() = { 1190.0f, 146.0f, 0.0f };
	pressEQuad->Pos() = { 1212.0f, 172.0f, 0.0f };
	pressQQuad->Pos() = { 1220.0f, 198.0f, 0.0f };
	pressBQuad->Scale() = { 125.0f, 23.0f, 0.0f };
	pressEQuad->Scale() = { 80.0f, 23.0f, 0.0f };
	pressQQuad->Scale() = { 65.0f, 23.0f, 0.0f };


	// 폰트 포스
	HpFontPos = {61.0f, 69.0f};
	BuildFontPos = { 61.0f, 69.0f };
	selPalLvFontPos = { 88.0f, 102.0f };
	selPalLvNumFontPos = { 100.0f, 108.0f };
	selPalNameFontPos = { 127.0f, 106.0f };
	palSpearTextFontPos = { 1034.0f, 117.0f, 0.0f };
	equipTextFontPos = { 1172.0f, 117.0f, 0.0f };
	pressBFontPos = { 1217.0f, 207.0f};
	pressEFontPos = { 1217.0f, 181.0f};
	pressQFontPos = { 1217.0f, 155.0f};

	parSpear100FontPos = { 1037.0f, 87.0f };
	parSpear010FontPos = { 1053.0f, 87.0f };
	parSpear001FontPos = { 1069.0f, 87.0f };
	ProjLoadNumFontPos = { 1225.0f, 96.0f };
	ProjTotalNumFontPos = { 1225.0f, 65.0f};


	// 플레이어 팔 매니저에 따라 세팅
	SetPalUI();

	// 테스트용
	fontPos = {};
	maxHp = 500;
	curHp = 500;
	tmpPalSpear = 123;
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
	delete icon_E2;
	delete icon_B;
	delete icon_MW;
	delete icon_Swap1;
	delete icon_Swap2;

	delete Pal1;
	delete Pal2;
	delete Pal3;
	delete PalQuad1;
	delete PalQuad2;
	delete PalQuad3;
	delete selPalQuad;
	delete selPalHpBar;

	delete palSpearTextQuad;
	delete palSpearRenderQuad;
	delete palSpearIcon;
	delete equipTextQuad;
	delete equipRenderQuad;
	delete equipIcon;
	delete equipSlash;
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
		//SetPalUI();
	}
	else if (KEY_DOWN('1')) // 왼쪽 팔 선택
	{
		selPal--;
		//SetPalUI();
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
	icon_E2->Update();
	icon_B ->Update();
	icon_MW->Update();
	icon_Swap1->Update();
	icon_Swap2->Update();
	Pal1->Update();
	Pal2->Update();
	Pal3->Update();
	PalQuad1->Update();
	PalQuad2->Update();
	PalQuad3->Update();
	selPalQuad->Update();
	selPalHpBar->Update();	
	palSpearTextQuad->Update();
	palSpearRenderQuad->Update();
	palSpearIcon->Update();
	equipTextQuad->Update();
	equipRenderQuad->Update();
	equipIcon->Update();
	equipSlash->Update();
	pressBQuad->Update();
	pressEQuad->Update();
	pressQQuad->Update();


	SetPalUI();

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
	icon_E->Render();
	icon_MW->Render();
	icon_Swap1->Render();
	icon_Swap2->Render();
	PalQuad1->Render();
	PalQuad2->Render();
	PalQuad3->Render();
	Pal1->Render();
	Pal2->Render();
	Pal3->Render();
	palSpearTextQuad->Render();
	palSpearRenderQuad->Render();
	palSpearIcon->Render();
	equipTextQuad->Render();
	equipRenderQuad->Render();
	equipIcon->Render();       // 얘는 나중에 플레이어 장비 받아와야함, 있으면 장비 랜더, 없으면 투명
	equipSlash->Render();
	pressBQuad->Render();
	pressEQuad->Render();
	pressQQuad->Render();
	icon_E2->Render();
	icon_B->Render();
	icon_Q->Render();

	// 폰트
	{
		// 체력
		string tmpString = to_string(curHp) + " / " + to_string(maxHp);
		//tmpString = "99";
		Font::Get()->SetStyle("HpUI");
		Font::Get()->RenderText(tmpString, { HpFontPos.x, HpFontPos.y });

		// 상호작용 안내
		tmpString = "건축";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });
		tmpString = "팰 소환";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });
		tmpString = "포획 스피어 투척";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });

		// 장비
		tmpString = "팰 스피어";
		Font::Get()->SetStyle("FieldEquibName");
		Font::Get()->RenderText(tmpString, { palSpearTextFontPos.x, palSpearTextFontPos.y }, 1);
		tmpString = "장비 뭐시기"; // 플레이어에서 가져와야 함
		Font::Get()->SetStyle("FieldEquibName");
		Font::Get()->RenderText(tmpString, { equipTextFontPos.x, equipTextFontPos.y }, 1);

		// 팰 스피어 개수
		Font::Get()->SetStyle("FieldNum1");
		int tmpT = tmpPalSpear; // *팰 스피어 개수 가져와야 함
		//int tmpT = PalSpearManager::Get()->GetSize(); // 팰스피어 매니저 말고 아이템 ui에서 가져와야 함
		if(tmpPalSpear >= 100) Font::Get()->SetColor("White");
		else Font::Get()->SetColor("Gray");
		tmpString = to_string(tmpT /100); // 백의 자리
		Font::Get()->RenderText(tmpString, { parSpear100FontPos.x, parSpear100FontPos.y },1);
		tmpT %= 100;

		if (tmpPalSpear >= 10) Font::Get()->SetColor("White");
		else Font::Get()->SetColor("Gray");
		tmpString = to_string(tmpT /10); // 십의 자리
		Font::Get()->RenderText(tmpString, { parSpear010FontPos.x, parSpear010FontPos.y },1);

		Font::Get()->SetColor("White");
		tmpT %= 10;
		tmpString = to_string(tmpT); // 일의 자리
		Font::Get()->RenderText(tmpString, { parSpear001FontPos.x, parSpear001FontPos.y },1);

		// *장비가 투사체가 있다면 출력, 무기에 투사체 유무 있어야 함
		Font::Get()->SetStyle("FieldNum3");
		Font::Get()->SetColor("Gray");

		int tmpBow = tmpPalSpear; // *투사체 개수 가져와야 함
		tmpString = to_string(tmpBow); // 투사체 총 개수, 아래에
		Font::Get()->RenderText(tmpString, { ProjTotalNumFontPos.x, ProjTotalNumFontPos.y }, 1);

		Font::Get()->SetStyle("FieldNum2");
		Font::Get()->SetColor("White");
		tmpBow = 8; //장전되어 있는 개수
		tmpString = to_string(tmpBow); // 투사체 장전되어있는 개수, 위에
		Font::Get()->RenderText(tmpString, { ProjLoadNumFontPos.x, ProjLoadNumFontPos.y }, 1);

		// 플레이 수행 안내
		tmpString = "건축"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressBFontPos.x, pressBFontPos.y }, 2);
		tmpString = "팰 소환"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressEFontPos.x, pressEFontPos.y }, 2);
		tmpString = "포획 스피어 투척"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressQFontPos.x, pressQFontPos.y }, 2);


		// 팰 선택
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
	//ImGui::SliderFloat("FontPosX 100", &parSpear100FontPos.x, 0, 1280);
	//ImGui::SliderFloat("FontPosY 100", &parSpear100FontPos.y, 0, 720);
	
	ImGui::SliderInt("PalSpearNum", &tmpPalSpear, 0, 999);

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
