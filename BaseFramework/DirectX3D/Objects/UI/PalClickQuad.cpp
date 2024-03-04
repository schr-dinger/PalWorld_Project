#include "Framework.h"

PalClickQuad::PalClickQuad()
{
	click = new Quad(size);
	click->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
}

PalClickQuad::~PalClickQuad()
{
}

void PalClickQuad::SetTexture()
{
	if (pal == nullptr)
	{
		click->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
	}
	else
	{
		click->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
	}
}
