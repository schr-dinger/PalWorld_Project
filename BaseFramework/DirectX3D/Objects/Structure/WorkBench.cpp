#include "Framework.h"
#include "WorkBench.h"

WorkBench::WorkBench()
{
	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);

	building = new Model("WorkBenchF");
	finished = new Model("WorkBench");
	cube = new Model("CubeModel");

	building->Rot().x = XM_PIDIV2;
	//finished->Rot().x = XM_PIDIV2;
	finished->SetParent(building);

	//Place();

	//light = Environment::Get()->GetLight(1);
	light = Environment::Get()->GetLight(2);
	light->type = 1;
	light->range = 0.01f;


	shadow = new FakeShadow();

	cube->Scale() *= 10;
	cube->Rot().y = XM_PIDIV4;

	range = new SphereCollider(5.0f);
	mouseHit = new SphereCollider(2.5f);

	produceBar = new ProgressBar(
		L"Textures/UI/gauge_bar.png",
		L"Textures/UI/hp_bar_BG.png"
	);
	WorkItem = nullptr;
}

WorkBench::~WorkBench()
{
	FOR(2) delete blendState[i];

	delete building;
	delete finished;
	delete center;
	delete cube;
	delete shadow;
	delete light;
	delete produceBar;
	delete WorkItem;
}

void WorkBench::Update()
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
	
	 

	if (KEY_PRESS('T') && PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(mouseHit))
	{
		Progressing = true;
		if (!PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = true;
	}
	else
	{
		Progressing = false;
		if (PlayerManager::Get()->GetPlayer()->isBuild) PlayerManager::Get()->GetPlayer()->isBuild = false;
		
	}

	if (off2 > 12.0f)
	{
		Done = true;
		UiManager::Get()->buildWorkBench = false;
	}


	if (UiManager::Get()->buildWorkBench)
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

void WorkBench::PreRender()
{
	if (!isPlaced) return;
	if (Done) return;

	shadow->SetRenderTarget(2);

	cube->SetShader(L"Light/DepthMap.hlsl");
	//cube->SetShader(L"Basic/Texture.hlsl");

	cube->Render();

}

void WorkBench::Render()
{
	if (!Done)
	{
		shadow->SetRender();
		building->SetShader(L"Light/Shadow.hlsl");
	}

	if (UiManager::Get()->buildWorkBench)
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

void WorkBench::PostRender()
{
	produceBar->Render();
}

void WorkBench::GUIRender()
{
}

void WorkBench::Place(float x, float z)
{
	if (isPlaced) return;

	building->Pos() = { x,LandScapeManager::Get()->GetTerrain()->GetHeight({x, 0, z}), z };
}

void WorkBench::Interaction()
{
	if (PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(range) && Done)
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		if (mouseHit->IsRayCollision(ray, &contact) && KEY_DOWN('F') && !UiManager::Get()->buildUiOn)
		{
			UiManager::Get()->WorkBenchUiOn = true;
		}

	}

	if (WorkItem != nullptr)
	{

		if (!CAM->ContainPoint(gaugePos) || abs((building->Pos() - PlayerManager::Get()->GetPlayer()->GlobalPos())
			.Length()) > 20) produceBar->SetActive(false);
		else produceBar->SetActive(true);


		produceBar->SetAmount(time / CompleteTime);


		gaugePos = building->Pos() + Vector3(0, 1.8f, 0);
		produceBar->Pos() = CAM->WorldToScreen(gaugePos);

		produceBar->Scale() = { 1.0f,0.5f,0.3f };

		produceBar->UpdateWorld();
		if (PlayerManager::Get()->GetPlayer()->GetPlayerCol()->IsCollision(mouseHit) && KEY_PRESS('Y'))
		{
			BarUpdate();
			PlayerManager::Get()->GetPlayer()->isWork = true;
		}
		else if ((KEY_UP('Y'))) PlayerManager::Get()->GetPlayer()->isWork = false;


	}
	else PlayerManager::Get()->GetPlayer()->isWork = false;


}

bool WorkBench::PalWorkCheck()
{
	if (isPlaced && !Done) return true;
	else	return false;
}

void WorkBench::SetItem(Item* item)
{
	if (WorkItem == nullptr)
	{
		time = 1;
		WorkItem = item;
		CompleteTime = WorkItem->MakeTime;
	}
}

void WorkBench::BarUpdate()
{
	if (time > CompleteTime)
	{
		produceBar->SetActive(false);

		time = 10;
		CompleteTime = 20;

		FOR(Count)
		{
			ItemManager::Get()->Mining(WorkItem);
		}
		WorkItem = nullptr;

		PlayerManager::Get()->GetPlayer()->isWork = false;
	}
	else
	{
		
		time += 10 * DELTA;
	}

}
