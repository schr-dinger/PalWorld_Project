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

	icon_B = new Quad(Vector2(1, 1));
	icon_B->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_KeyGuide_Keyboard_B.png");
	icon_B->SetTag("iB");
	icon_B->Scale().x = 20.0f;
	icon_B->Scale().y = 20.0f;

	// �� ������
	Pal1= new Quad(Vector2(1, 1));
	Pal2= new Quad(Vector2(1, 1));
	Pal3= new Quad(Vector2(1, 1));
	Pal1->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTexture());
	Pal2->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTexture());
	Pal3->GetMaterial()->SetDiffuseMap(PlayerPalsManager::Get()->GetPal(0)->GetTexture());
	Pal1->Scale() = {80.0f, 80.0f, 0.0f};
	Pal2->Scale() = {50.0f, 50.0f, 0.0f};
	Pal3->Scale() = { 50.0f, 50.0f, 0.0f};
	Pal1->SetTag("P1");
	Pal2->SetTag("P2");
	Pal3->SetTag("P3");
	Pal1->Pos() = { 136.6f, 170.0f, 0.0f };
	Pal2->Pos() = { 56.0f, 155.0f, 0.0f };
	Pal3->Pos() = { 217.0f, 155.0f, 0.0f };

	// �� ���� ������
	PalQuad1 = new Quad(Vector2(1, 1));
	PalQuad2 = new Quad(Vector2(1, 1));
	PalQuad3 = new Quad(Vector2(1, 1));
	PalQuad1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	PalQuad2->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	PalQuad3->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	PalQuad1->Scale() = { 80.0f, 80.0f, 0.0f };
	PalQuad2->Scale() = { 50.0f, 50.0f, 0.0f };
	PalQuad3->Scale() = { 50.0f, 50.0f, 0.0f };
	PalQuad1->SetTag("PQ1");
	PalQuad2->SetTag("PQ2");
	PalQuad3->SetTag("PQ3");
	PalQuad1->Pos() = { 136.6f, 170.0f, 0.0f };
	PalQuad2->Pos() = { 56.0f, 155.0f, 0.0f };
	PalQuad3->Pos() = { 217.0f, 155.0f, 0.0f };


	// ��Ʈ ����
	HpFontPos = {61.0f, 69.0f};
	BuildFontPos = { 61.0f, 69.0f };

	// ��Ʈ �׽�Ʈ��
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

}	

void FieldUI::Update()
{
	hpBar  ->Update();
	hgyBar ->Update();
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
	//��Ʈ
	{
		// ü��
		string tmpString = to_string(curHp) + " / " + to_string(maxHp);
		//tmpString = "99";
		Font::Get()->SetStyle("HpUI");
		Font::Get()->RenderText(tmpString, { HpFontPos.x, HpFontPos.y });

		//Font::Get()->SetColor("Gray");
		//tmpString = "/" + to_string(500);
		//Font::Get()->RenderText(tmpString, { fontPos.x + 10, fontPos.y });

		//Font::Get()->SetColor("White");
		Font::Get()->SetStyle("Default");
		Font::Get()->GetDC()->EndDraw();
		Font::Get()->GetDC()->BeginDraw();
	}

	
}

void FieldUI::GUIRender()
{
	//ImGui::SliderFloat("FontPosX", &fontPos.x, 0, 1280);
	//ImGui::SliderFloat("FontPosY", &fontPos.y, 0, 720);
	//ImGui::SliderInt("CurHp: %d", &curHp, 0, maxHp);
	icon_1->GUIRender();
	icon_2->GUIRender();
	icon_3->GUIRender();
	icon_Q->GUIRender();
	icon_E->GUIRender();
	icon_B->GUIRender();
	

}
