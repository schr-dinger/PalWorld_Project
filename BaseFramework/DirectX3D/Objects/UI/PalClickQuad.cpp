#include "Framework.h"

PalClickQuad::PalClickQuad()
{
	click = new Quad(size);
	click->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");

	pal = nullptr;
}

PalClickQuad::~PalClickQuad()
{
}

void PalClickQuad::SetTexture()
{
	if (pal == nullptr)
	{
		click->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	}
	else
	{
		//click->GetMaterial()->SetDiffuseMap(L"Textures/UI/PalIcon/T_Penguin_icon_normal.png");
		click->GetMaterial()->SetDiffuseMap(pal->GetTexture());
	}
}
