#include "Framework.h"

Ice::Ice(string name) : Model("IceAttack")
{
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);
	//blendState[1]->AlphaToCoverage(true);

	Rot().x = XM_PIDIV2;
}

Ice::~Ice()
{
	FOR(2) delete blendState[i];
}

void Ice::Update()
{
	Model::UpdateWorld();
}

void Ice::Render()
{
	blendState[1]->SetState();
	Model::Render();
	blendState[0]->SetState();

}

void Ice::GUIRender()
{
	Model::GUIRender();
}

void Ice::Attack()
{
}
