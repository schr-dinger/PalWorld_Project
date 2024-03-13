#include "Framework.h"

FieldUI::FieldUI()
{
	// �÷��̾� ü�� ����� ��
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
	// �� ���ʿ� �ִ� ü��, ����� ������
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


	// Ű ������
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

	// �� ������
	Pal1= new Quad(Vector2(1, 1));
	Pal2= new Quad(Vector2(1, 1));
	Pal3= new Quad(Vector2(1, 1));
	//Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTextureC());  // �׽�Ʈ��
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

	// �� ���� ������
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

	// �� ����
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

	// �÷��̾� ���
	// �ӽ��Ǿ�
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
	// ���(Ȱ, ��, ����...)
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

	// �÷��� ����
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


	// ��Ʈ ����
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


	// �÷��̾� �� �Ŵ����� ���� ����
	SetPalUI();

	// �׽�Ʈ��
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
	// �� ����
	if (KEY_DOWN('E')) // ���� �� ��ȯ
	{
		if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
		{
			PlayerPalsManager::Get()->SetSelPal(selPal);
			PlayerPalsManager::Get()->Summons();
		}
	}
	else if (KEY_DOWN('3')) // ������ �� ����
	{
		selPal++;
		//SetPalUI();
	}
	else if (KEY_DOWN('1')) // ���� �� ����
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
	equipIcon->Render();       // ��� ���߿� �÷��̾� ��� �޾ƿ;���, ������ ��� ����, ������ ����
	equipSlash->Render();
	pressBQuad->Render();
	pressEQuad->Render();
	pressQQuad->Render();
	icon_E2->Render();
	icon_B->Render();
	icon_Q->Render();

	// ��Ʈ
	{
		// ü��
		string tmpString = to_string(curHp) + " / " + to_string(maxHp);
		//tmpString = "99";
		Font::Get()->SetStyle("HpUI");
		Font::Get()->RenderText(tmpString, { HpFontPos.x, HpFontPos.y });

		// ��ȣ�ۿ� �ȳ�
		tmpString = "����";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });
		tmpString = "�� ��ȯ";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });
		tmpString = "��ȹ ���Ǿ� ��ô";
		Font::Get()->SetStyle("FieldLv");
		//Font::Get()->RenderText(tmpString, { fontPos.x, fontPos.y });

		// ���
		tmpString = "�� ���Ǿ�";
		Font::Get()->SetStyle("FieldEquibName");
		Font::Get()->RenderText(tmpString, { palSpearTextFontPos.x, palSpearTextFontPos.y }, 1);
		tmpString = "��� ���ñ�"; // �÷��̾�� �����;� ��
		Font::Get()->SetStyle("FieldEquibName");
		Font::Get()->RenderText(tmpString, { equipTextFontPos.x, equipTextFontPos.y }, 1);

		// �� ���Ǿ� ����
		Font::Get()->SetStyle("FieldNum1");
		int tmpT = tmpPalSpear; // *�� ���Ǿ� ���� �����;� ��
		//int tmpT = PalSpearManager::Get()->GetSize(); // �ӽ��Ǿ� �Ŵ��� ���� ������ ui���� �����;� ��
		if(tmpPalSpear >= 100) Font::Get()->SetColor("White");
		else Font::Get()->SetColor("Gray");
		tmpString = to_string(tmpT /100); // ���� �ڸ�
		Font::Get()->RenderText(tmpString, { parSpear100FontPos.x, parSpear100FontPos.y },1);
		tmpT %= 100;

		if (tmpPalSpear >= 10) Font::Get()->SetColor("White");
		else Font::Get()->SetColor("Gray");
		tmpString = to_string(tmpT /10); // ���� �ڸ�
		Font::Get()->RenderText(tmpString, { parSpear010FontPos.x, parSpear010FontPos.y },1);

		Font::Get()->SetColor("White");
		tmpT %= 10;
		tmpString = to_string(tmpT); // ���� �ڸ�
		Font::Get()->RenderText(tmpString, { parSpear001FontPos.x, parSpear001FontPos.y },1);

		// *��� ����ü�� �ִٸ� ���, ���⿡ ����ü ���� �־�� ��
		Font::Get()->SetStyle("FieldNum3");
		Font::Get()->SetColor("Gray");

		int tmpBow = tmpPalSpear; // *����ü ���� �����;� ��
		tmpString = to_string(tmpBow); // ����ü �� ����, �Ʒ���
		Font::Get()->RenderText(tmpString, { ProjTotalNumFontPos.x, ProjTotalNumFontPos.y }, 1);

		Font::Get()->SetStyle("FieldNum2");
		Font::Get()->SetColor("White");
		tmpBow = 8; //�����Ǿ� �ִ� ����
		tmpString = to_string(tmpBow); // ����ü �����Ǿ��ִ� ����, ����
		Font::Get()->RenderText(tmpString, { ProjLoadNumFontPos.x, ProjLoadNumFontPos.y }, 1);

		// �÷��� ���� �ȳ�
		tmpString = "����"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressBFontPos.x, pressBFontPos.y }, 2);
		tmpString = "�� ��ȯ"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressEFontPos.x, pressEFontPos.y }, 2);
		tmpString = "��ȹ ���Ǿ� ��ô"; 
		Font::Get()->SetStyle("FieldPlay");
		Font::Get()->RenderText(tmpString, { pressQFontPos.x, pressQFontPos.y }, 2);


		// �� ����
		if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr) // ���� ���� �� ����, ����, �̸� ����
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
	// ���� �� ���µ��� ����ϱ�
	//if (PlayerPalsManager::Get()->GetPal(selPal) != nullptr)
	//{
	//	Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(selPal)->GetTextureC());
	//}
	//else
	//{
	//	Pal1->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}
	//int tmp1 = (selPal + 1) % 5; // �������� ������ �ִ� ��
	//if (PlayerPalsManager::Get()->GetPal(tmp1) != nullptr)
	//{
	//	Pal3->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(tmp1)->GetTextureC());
	//}
	//else
	//{
	//	Pal3->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}
	//int tmp2 = (selPal + 4) % 5; // ������ ���� �ִ� ��
	//if (PlayerPalsManager::Get()->GetPal(tmp2) != nullptr)
	//{
	//	Pal2->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(tmp2)->GetTextureC());
	//}
	//else
	//{
	//	Pal2->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	//}


	// ����ó�� ���� �׽�Ʈ
	int test[3] = {-1, -1, -1};
	int tmp = 0;

	if (KEY_DOWN('1')) // ���� �� ����
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
