#include "Framework.h"

PalBox::PalBox(Terrain* terrain) : terrain(terrain)
{
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);

	Place();
}

PalBox::~PalBox()
{
	FOR(2) delete blendState[i];
}

void PalBox::Update()
{
}

void PalBox::Render()
{
	blendState[1]->SetState();
	Model::Render();
	blendState[0]->SetState();
}

void PalBox::GUIRender()
{
}

void PalBox::Place()
{
	Pos() = { 100,terrain->GetHeight({100, 0, 100}),100 };
}
