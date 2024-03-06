#include "Framework.h"

PalClickQuad::PalClickQuad()
{
	click = new Quad(size);
	click->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");

	pal = nullptr;
}

PalClickQuad::~PalClickQuad()
{
	delete click;
	delete pal;
}

void PalClickQuad::Update()
{
	click->Update();
}

void PalClickQuad::Render()
{
	click->Render();
}

void PalClickQuad::PostRender()
{
}

void PalClickQuad::GuiRender()
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

bool PalClickQuad::MouseCollision()
{
	float minX = click->Pos().x - click->GetSize().x * 0.5f;
	float maxX = click->Pos().x + click->GetSize().x * 0.5f;
	float minY = click->Pos().y - click->GetSize().y * 0.5f;
	float maxY = click->Pos().y + click->GetSize().y * 0.5f;

	if (minX < mousePos.x && maxX > mousePos.x && minY < mousePos.y && maxY > mousePos.y)
	{
		return true;
	}

	return false;
}
