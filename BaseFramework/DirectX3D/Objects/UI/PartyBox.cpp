#include "Framework.h"

PartyBox::PartyBox()
{
	// ¹æ½Ä 4°³
	//partyBox1 = new Quad(Vector2(100, 40));
	//partyBox = nullptr;
	//partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
	//partyBox1 = new Quad(L"Textures/UI/T_prt_menu_state_base.png");


	partyBox1 = new Quad(Vector2(1, 1));
	partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
	//partyBox1 = new Quad(L"Textures/UI/T_prt_pal_base.png");
	//partyBox2 = new Quad(L"Textures/UI/T_prt_pal_base_frame.png");
	partyBox2 = new Quad(Vector2(1, 1));
	partyBox2->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
	partyBox2->SetActive(false);
	partyBox1->Scale().x *= 250;
	partyBox1->Scale().y *= 65;
	partyBox2->Scale().x *= 250;
	partyBox2->Scale().y *= 65;

	//partyBox1->GetMaterial()->GetData().diffuse.w = 0.5;

	pickState = PickState::RELEASE;

	pal = PlayerPalsManager::Get()->GetPal(0);
	//pal->GetTexture();
	//partyBox2->GetMaterial()->SetDiffuseMap(pal->GetTexture());

	partyBox3 = new Quad(Vector2(1, 1));
	partyBox3->GetMaterial()->SetDiffuseMap(pal->GetTexture());
	partyBox3->Scale().x *= 65;
	partyBox3->Scale().y *= 65;
	partyBox3->SetTag("Icon");

	partyBox4 = new Quad(Vector2(1, 1));
	partyBox4->GetMaterial()->SetDiffuseMap(pal->GetTexture());
	partyBox4->Scale().x *= 65;
	partyBox4->Scale().y *= 65;
	partyBox4->SetActive(false);

	hpBar = new ProgressBar(
		L"Textures/Color/Red.png",
		L"Textures/Color/BlackGlass50.png"
	);
	hpBar->SetTag("hp");
	hpBar->Scale().x = 0.6f;
	hpBar->Scale().y = 0.05f;

	hgyBar = new ProgressBar(
		L"Textures/Color/Green.png",
		L"Textures/Color/BlackGlass50.png"
	);
	hgyBar->SetTag("hgy");
	hgyBar->Scale().x = 0.6f;
	hgyBar->Scale().y = 0.02f;
}

PartyBox::~PartyBox()
{
}

void PartyBox::Update()
{
	partyBox2->Pos() = partyBox1->Pos();
	partyBox3->Pos() = partyBox1->Pos() + Vector3(93.0f, 0.0f, 0.0f);
	hpBar->Pos() = partyBox1->Pos() + Vector3(-29.0f, -6.3f, 0);
	hgyBar->Pos() = partyBox1->Pos() + Vector3(-29.0f, -20.3f, 0);

	Collision();

	
	partyBox1->UpdateWorld();
	partyBox2->UpdateWorld();
	partyBox3->UpdateWorld();
	partyBox4->UpdateWorld();
	hpBar->Update();
	hgyBar->Update();
}

void PartyBox::PostRender()
{
	partyBox1->Render();
	partyBox3->Render();
	hpBar->Render();
	hgyBar->Render();

	partyBox2->Render();
	partyBox4->Render();

}

void PartyBox::GUIRender()
{
	//partyBox4->GUIRender();
	partyBox1->GUIRender();
	hpBar->GUIRender();
	hgyBar->GUIRender();

	ImGui::Text("Mouse.x : %f", mousePos.x);
	ImGui::Text("Mouse.y : %f", mousePos.y);

}

void PartyBox::Collision()
{
	float left = partyBox1->Pos().x - partyBox1->GetSize().x * 0.5 * partyBox1->Scale().x;
	float right = partyBox1->Pos().x + partyBox1->GetSize().x * 0.5 * partyBox1->Scale().x;
	float top = partyBox1->Pos().y + partyBox1->GetSize().y * 0.5 * partyBox1->Scale().y;
	float bottom = partyBox1->Pos().y - partyBox1->GetSize().y * 0.5 * partyBox1->Scale().y;

	switch (pickState)
	{
	case PartyBox::PickState::RELEASE:
		if (mousePos.x <= right && mousePos.x >= left && mousePos.y <= top && mousePos.y >= bottom)
		{
			partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
			if (KEY_DOWN(VK_LBUTTON))
			{
				pickState = PickState::PICKING;
				partyBox2->SetActive(true);
				partyBox4->SetActive(true);

			}
		}
		else
		{
			//partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
			partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		}

		break;
	case PartyBox::PickState::PICKING:
		partyBox2->Pos() = mousePos + Vector3(130.0f, -40.0f, 0.0f);
		partyBox4->Pos() = partyBox2->Pos() + Vector3(93.0f, 0.0f, 0.0f);

		if (KEY_DOWN(VK_LBUTTON))
		{
			pickState = PickState::RELEASE;
			partyBox1->Pos() = partyBox2->Pos();
			partyBox2->SetActive(false);
			partyBox4->SetActive(false);


		}
		break;
	default:
		break;
	}


	
}
