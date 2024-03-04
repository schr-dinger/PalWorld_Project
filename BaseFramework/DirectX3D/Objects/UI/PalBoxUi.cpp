#include "Framework.h"
#include "PalBoxUi.h"

PalBoxUi::PalBoxUi()
{
	boxBase = new Quad(L"Textures/UI/T_gauge_HP_base.png");
	boxBase->Pos() = { 640,360,0 };
	boxBase->Scale() *= 5.0f;
	boxBase->Scale().y *= 4.0f;



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

	boxBase->Render();
}

void PalBoxUi::GuiRender()
{
}
