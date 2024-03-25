#include "Framework.h"
#include "LoadingScene_2.h"
#include "Scenes/GameScene/BossScene.h"

int bossCount = 0;
mutex u;

void BossSceneLoading()
{
	u.lock();
	Scene* tmp = new BossScene();
	SceneManager::Get()->Create("BossScene", tmp);
	SceneManager::Get()->Add("BossScene");
	tmp->Update();
	tmp->PreRender();
	tmp->Render();
	tmp->PostRender();
	bossCount++;
	u.unlock();

}


LoadingScene_2::LoadingScene_2()
{
	//titleBg = new Quad(Vector2(3840,2160));
	titleBg = new Quad(Vector2(1280, 720));

	titleBg->Pos() = middle;
	titleBg->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_title_BG.png");
	titleBg->UpdateWorld();


	loadingBar = new ProgressBar(L"Textures/Color/White.png", L"Textures/Color/WhiteGlass30.png");
	loadingBar->Pos() = middle + Vector3(0.0f, -300.0f, 0.0f);
	loadingBar->Scale().x *= 4.0f;
	loadingBar->Scale().y *= 0.2f;


}

LoadingScene_2::~LoadingScene_2()
{
	th->join();
	delete th;
	delete titleBg;
	delete loadingBar;
}

void LoadingScene_2::Update()
{
	fakeT += DELTA;

	if (fakeT > RANDOM->Float(2.0f, 3.0f) && bossCount < 5)
	{
		bossCount++;
		fakeT = 0.0f;
	}
	else if (fakeT > RANDOM->Float(1.0f, 4.0f))
	{
		bossCount++;
		fakeT = 0.0f;
	}


	if (!first && bossCount == 4)
	{
		th = new thread(BossSceneLoading);
		first = true;
	}

	loadingBar->SetAmount((float)bossCount / 10.0f);
	loadingBar->Update();

	if (bossCount == 10)
	{
		SceneManager::Get()->ChangeScene("BossScene");
		SceneManager::Get()->Remove("Loading_2");

		return;
	}
}

void LoadingScene_2::PreRender()
{
}

void LoadingScene_2::Render()
{
}

void LoadingScene_2::PostRender()
{
	titleBg->Render();
	loadingBar->Render();
}

void LoadingScene_2::GUIRender()
{
	loadingBar->GUIRender();
}

