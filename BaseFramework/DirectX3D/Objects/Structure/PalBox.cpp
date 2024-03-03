#include "Framework.h"

PalBox::PalBox()
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
		isBuilding = false;
	}


	if (KEY_DOWN('B'))
	{
		isBuilding = !isBuilding;
	}

	if (isBuilding)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			isPlaced = true;
		}
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
	if (!Done)
	{
		shadow->SetRender();
		building->SetShader(L"Light/Shadow.hlsl");
	}

	if (isBuilding)
	{
		//shadow->SetRender();
		//building->SetShader(L"Light/Shadow.hlsl");
		blendState[1]->SetState();
		building->Render();
		blendState[0]->SetState();

	}

	if (Done)
	{
		blendState[1]->SetState();
		finished->Render();
		blendState[0]->SetState();
	}
}

void PalBox::PostRender()
{
	//shadow->PostRender();
}

void PalBox::GUIRender()
{
	cube->GUIRender();

	ImGui::Text("%f", off2);
}

void PalBox::Place(float x, float z)
{
	if(isPlaced) return;

	building->Pos() = { x,LandScapeManager::Get()->GetTerrain()->GetHeight({x, 0, z}), z };
}
