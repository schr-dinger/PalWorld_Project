#include "Framework.h"

PartyBox::PartyBox()
{
	partyBox1 = new Quad(Vector2(100, 40));
	//partyBox = new Quad(L"Textures/UI/IconFrame.png");
	//partyBox = nullptr;
	partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
}

PartyBox::~PartyBox()
{
}

void PartyBox::Update()
{
	partyBox1->UpdateWorld();
	Collision();
}

void PartyBox::PostRender()
{
	partyBox1->Render();

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


	if (mousePos.x <= right && mousePos.x >= left && mousePos.y <= top && mousePos.y >= bottom)
	{
		partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		if (KEY_PRESS(VK_LBUTTON))
		{
			partyBox1->Pos() = mousePos;
			partyBox1->UpdateWorld();
		}
	}
	else
	{
		//partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
		partyBox1->GetMaterial()->SetDiffuseMap(L"Textures/UI/IconFrame.png");
	}
}
