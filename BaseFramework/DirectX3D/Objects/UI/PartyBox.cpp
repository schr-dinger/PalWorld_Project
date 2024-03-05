#include "Framework.h"

PartyBox::PartyBox()
{
	// ¹æ½Ä 4°³
	//partyBox1 = new Quad(Vector2(100, 40));
	//partyBox = nullptr;
	//partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
	//partyBox1 = new Quad(L"Textures/UI/T_prt_menu_state_base.png");


	partyBox1 = new Quad(Vector2(1, 1));
	partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
	//partyBox1 = new Quad(L"Textures/UI/T_prt_pal_base.png");
	//partyBox2 = new Quad(L"Textures/UI/T_prt_pal_base_frame.png");
	partyBox2 = new Quad(Vector2(1, 1));
	partyBox2->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
	partyBox2->SetActive(false);
	partyBox1->Scale().x *= 250;
	partyBox1->Scale().y *= 65;
	partyBox2->Scale().x *= 250;
	partyBox2->Scale().y *= 65;

	//partyBox1->GetMaterial()->GetData().diffuse.w = 0.5;

	pickState = PickState::RELEASE;

	pal = PlayerPalsManager::Get()->GetPal(0);
}

PartyBox::~PartyBox()
{
}

void PartyBox::Update()
{
	partyBox2->Pos() = partyBox1->Pos();
	Collision();

	
	partyBox1->UpdateWorld();
	partyBox2->UpdateWorld();
}

void PartyBox::PostRender()
{
	partyBox1->Render();
	partyBox2->Render();

}

void PartyBox::GUIRender()
{
	partyBox1->GUIRender();
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
			partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlueGlass.png");
			if (KEY_DOWN(VK_LBUTTON))
			{
				pickState = PickState::PICKING;
				partyBox2->SetActive(true);

			}
		}
		else
		{
			//partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
			partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
		}

		break;
	case PartyBox::PickState::PICKING:
		partyBox2->Pos() = mousePos;
		if (KEY_DOWN(VK_LBUTTON))
		{
			pickState = PickState::RELEASE;
			partyBox1->Pos() = partyBox2->Pos();
			partyBox2->SetActive(false);


		}
		break;
	default:
		break;
	}


	
}
