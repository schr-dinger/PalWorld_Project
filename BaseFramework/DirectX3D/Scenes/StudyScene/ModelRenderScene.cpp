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
		Spike[i]->GetMaterial(0)->SetDiffuseMap(L"Textures/Model/Spike/T_Rock01_color.png");

		particle[i] = new ParticleSystem("TextData/Particles/test2.fx");

	}

	test = new Quad(Vector2(100, 100));
	test->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedTest2.png");
}

ModelRenderScene::~ModelRenderScene()
{
	FOR(3)
	{
		delete Spike[i];
		delete particle[i];
	}
}

void ModelRenderScene::Update()
{

	test->Pos() = Vector3(400, 400, 0);
	test->Update();

	FOR(3)
	{
		if (KEY_PRESS('H'))
		{
			particle[i]->Play(Vector3(0, 5, (i + 1) * 5));
			if (Spike[i]->Pos().y < 0)  Spike[i]->Pos().y += (i+20) * DELTA;
		}
		if (KEY_DOWN('J'))
		{
			Spike[i]->Pos() = Vector3(0, -10, (i + 1) * 5);
		}

		particle[i]->Update();
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
		particle[i]->Render();
		Spike[i]->Render();

	}

}

void ModelRenderScene::PostRender()
{
	test->Render();
}

void ModelRenderScene::GUIRender()
{
	FOR(3)
	{
		Spike[i]->GUIRender();

	}
	test->GUIRender();

}
