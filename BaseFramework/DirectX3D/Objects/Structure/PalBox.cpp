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
	light = Environment::Get()->GetLight(1);
	light->type = 1;
	light->range = 0.01f;


	shadow = new FakeShadow();

	cube->Scale() *= 10;
	cube->Rot().y = XM_PIDIV4;

	range = new SphereCollider(5.0f);
	mouseHit = new SphereCollider(2.5f);
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
	//Place(PlayerManager::Get()->GetPlayer()->GetFrontPoint()->Pos().x, PlayerManager::Get()->GetPlayer()->GetFrontPoint()->Pos().y);

	cube->Pos().x = building->Pos().x;
	cube->Pos().z = building->Pos().z;
	cube->Pos().y = building->Pos().y + off2;

	range->Pos() = building->Pos();
	mouseHit->Pos() = building->Pos();


	light->pos = building->Pos() + off;


	if (Progressing && isPlaced)
	{
		off2 += 0.5f * DELTA;
		
	}
	

	//if (KEY_PRESS('P'))
	//{
	//	Progressing = true;
	//	
	//}
	//else
	//{
	//	Progressing = false;
	//	
	//}

	if (KEY_PRESS('F') && PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(mouseHit)
		&& !Done)
	{
		Progressing = true;
		if (!PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = true;
	}
	else if(KEY_UP('F'))
	{
		Progressing = false;
		if (PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = false;

	}





	if (off2 > 13.0f)
	{
		Done = true;
		if (PlayerManager::Get()->GetPlayer()->isBuild && UiManager::Get()->buildPalBox) PlayerManager::Get()->GetPlayer()->isBuild = false;
		UiManager::Get()->buildPalBox = false;
		
	}


	if (UiManager::Get()->buildPalBox)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			isPlaced = true;
		}
	}
	//상호작용 함수
	Interaction();

	cube->UpdateWorld();
	building->UpdateWorld();
	finished->UpdateWorld();
	range->UpdateWorld();
	mouseHit->UpdateWorld();
}

void PalBox::PreRender()
{
	if (!isPlaced) return;
	if (Done) return;

	shadow->SetRenderTarget(1);

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

	if (UiManager::Get()->buildPalBox)
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

	range->Render();
	mouseHit->Render();

}

void PalBox::PostRender()
{
	//shadow->PostRender();
}

void PalBox::GUIRender()
{
	cube->GUIRender();
}

void PalBox::Place(float x, float z)
{
	if(isPlaced) return;

	building->Pos() = { x,LandScapeManager::Get()->GetTerrain()->GetHeight({x, 0, z}), z };
}

void PalBox::Interaction()
{
	if (PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(range) && Done)
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		if (mouseHit->IsRayCollision(ray, &contact) && KEY_DOWN('F') && !UiManager::Get()->buildUiOn)
		{
			UiManager::Get()->palBoxUiOn = true;
			UiManager::Get()->SetPalBoxUI();

		}

	}

}

bool PalBox::PalWorkCheck()
{
	if (isPlaced && !Done) return true;
	else	return false;

}
