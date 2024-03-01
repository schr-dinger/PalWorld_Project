#include "Framework.h"

PalBox::PalBox(Terrain* terrain) : terrain(terrain)
{
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);

	building = new Model("PalBoxF");
	finished = new Model("PalBox");
	cube = new Model("CubeModel");

	building->Rot().x = XM_PIDIV2;
	//finished->Rot().x = XM_PIDIV2;
	finished->SetParent(building);

	//Place();

	//light = Environment::Get()->GetLight(1);
	light = Environment::Get()->AddLight();
	light->type = 1;
	light->range = 0.01f;


	shadow = new Shadow();

	cube->Scale() *= 10;
	cube->Rot().y = XM_PIDIV4;
}

PalBox::~PalBox()
{
	FOR(2) delete blendState[i];

	delete building;
	delete finished;
	delete center;
	delete cube;
	delete shadow;
	delete light;
}

void PalBox::Update()
{
	cube->Pos().x = building->Pos().x;
	cube->Pos().z = building->Pos().z;
	cube->Pos().y = building->Pos().y + off2;

	light->pos = building->Pos() + off;


	if (Progressing)
	{
		off2 += 0.5f * DELTA;
	}

	if (KEY_PRESS('P'))
	{
		Progressing = true;
	}
	else
	{
		Progressing = false;
	}

	if (off2 > 13.0f)
	{
		Done = true;
	}

	cube->UpdateWorld();
	building->UpdateWorld();
	finished->UpdateWorld();
}

void PalBox::PreRender()
{
	shadow->SetRenderTarget();

	cube->SetShader(L"Light/DepthMap.hlsl");
	//cube->SetShader(L"Basic/Texture.hlsl");

	cube->Render();

}

void PalBox::Render()
{
	shadow->SetRender();
	building->SetShader(L"Light/Shadow.hlsl");
	//building->SetShader(L"Basic/Texture.hlsl");

	//

	blendState[1]->SetState();

	if (Done)
	{
		finished->Render();
	}
	else
	{
		building->Render();
	}

	blendState[0]->SetState();
}

void PalBox::PostRender()
{
	shadow->PostRender();
}

void PalBox::GUIRender()
{
	cube->GUIRender();

	ImGui::Text("%f", off2);
}

void PalBox::Place(float x, float z)
{
	if(isPlaced) return;

	building->Pos() = { x,terrain->GetHeight({x, 0, z}), z };
}
