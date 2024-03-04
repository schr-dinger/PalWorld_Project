#include "Framework.h"

PartyBox::PartyBox()
{
	//partyBox = new Quad(Vector2(100, 40));
	partyBox = new Quad(L"Textures/UI/IconFrame.png");
	//partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");

}

PartyBox::~PartyBox()
{
}

void PartyBox::Update()
{
	partyBox->UpdateWorld();
	Collision();
}

void PartyBox::Render()
{
}

void PartyBox::PostRender()
{
	partyBox->Render();

}

void PartyBox::GUIRender()
{
	partyBox->GUIRender();
	ImGui::Text("Mouse.x : %f", mousePos.x);
	ImGui::Text("Mouse.y : %f", mousePos.y);

}

void PartyBox::Collision()
{
	float left = partyBox->Pos().x - partyBox->GetSize().x * 0.5 * partyBox->Scale().x;
	float right = partyBox->Pos().x + partyBox->GetSize().x * 0.5 * partyBox->Scale().x;
	float top = partyBox->Pos().y + partyBox->GetSize().y * 0.5 * partyBox->Scale().y;
	float bottom = partyBox->Pos().y - partyBox->GetSize().y * 0.5 * partyBox->Scale().y;


	if (mousePos.x < right && mousePos.x > left && mousePos.y < top && mousePos.y > bottom)
	{
		partyBox->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		if (KEY_PRESS(VK_LBUTTON))
		{
			partyBox->Pos() = mousePos;
			partyBox->UpdateWorld();
		}
	}
	else
	{
		//partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");
		partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/IconFrame.png");
	}
}
