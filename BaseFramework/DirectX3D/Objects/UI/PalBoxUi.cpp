#include "Framework.h"
#include "PalBoxUi.h"

PalBoxUi::PalBoxUi()
{
	//boxBase = new Quad(L"Textures/UI/T_gauge_HP_base.png");
	boxBase = new Quad(baseSize);
	boxBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
	boxBase->Pos() = { 640,400,0 };


	FOR(30)
	{
		boxIcon[i] = new PalClickQuad();
		boxIcon[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0)*70.0f;
	}

}

PalBoxUi::~PalBoxUi()
{
	delete boxBase;
}

void PalBoxUi::Update()
{
	FOR(30)
	{
		boxIcon[i]->Update();
	}

	boxBase->Update();
}

void PalBoxUi::Render()
{
}

void PalBoxUi::PostRender()
{
	boxBase->Render();
	FOR(30)
	{
		boxIcon[i]->Render();
	}

}

void PalBoxUi::GuiRender()
{
}
