#include "Framework.h"
#include "PalBoxUi.h"

PalBoxUi::PalBoxUi()
{
	//boxBase = new Quad(L"Textures/UI/T_gauge_HP_base.png");
	boxBase = new Quad(baseSize);
	boxBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
	boxBaseFrame = new Quad(baseSize+Vector2(5,5));
	boxBaseFrame->SetParent(boxBase);
	boxBaseFrame->GetMaterial()->SetDiffuseMap(L"Textures/Color/Glass.png");

	boxBase->Pos() = { 640,360,0 };


	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			boxIcon[x][y] = new PalClickQuad();
			boxIcon[x][y]->GetQuad()->Pos() = { 55.0f * x,55.0f * y,0 };

		}
	}

}

PalBoxUi::~PalBoxUi()
{
	delete boxBase;
	delete boxBaseFrame;
}

void PalBoxUi::Update()
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			boxIcon[x][y]->Update();
		}
	}

	boxBase->Update();
	boxBaseFrame->Update();

}

void PalBoxUi::Render()
{
}

void PalBoxUi::PostRender()
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			boxIcon[x][y]->Render();
		}
	}

	//boxBaseFrame->Render();
	boxBase->Render();

}

void PalBoxUi::GuiRender()
{
}
