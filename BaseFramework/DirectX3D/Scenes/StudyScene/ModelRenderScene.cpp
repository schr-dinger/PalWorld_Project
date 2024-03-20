#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
	FOR(3)
	{
		Spike[i] = new Model("Spike");
		Spike[i]->Rot().x += XM_PIDIV2;
		Spike[i]->Scale() *= 10.0f;

		Spike[i]->Pos() = Vector3(0, -10, (i + 1) * 5);

	}
}

ModelRenderScene::~ModelRenderScene()
{
	FOR(3)
	{
		delete Spike[i];

	}
}

void ModelRenderScene::Update()
{

	

	FOR(3)
	{
		if (KEY_PRESS('H'))
		{
			if (Spike[i]->Pos().y < 0)  Spike[i]->Pos().y += (i+10) * DELTA;
		}
		if (KEY_DOWN('J'))
		{
			Spike[i]->Pos() = Vector3(0, -10, (i + 1) * 5);
		}

		Spike[i]->UpdateWorld();

	}
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
	FOR(3)
	{
		Spike[i]->Render();

	}

}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    
}
