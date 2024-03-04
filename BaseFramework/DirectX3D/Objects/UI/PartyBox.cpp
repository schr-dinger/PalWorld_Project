#include "Framework.h"

PartyBox::PartyBox()
{
	partyBox = new Quad(Vector2(100, 40));
	partyBox->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_prt_get_reticle_per_base-1.png");

}

PartyBox::~PartyBox()
{
}

void PartyBox::Update()
{
	partyBox->UpdateWorld();
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
}
