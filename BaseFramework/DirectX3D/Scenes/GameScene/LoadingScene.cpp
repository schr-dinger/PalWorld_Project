#include "Framework.h"
#include "LoadingScene.h"
#include "Scenes/GameScene/BaseScene1.h"

int initCount = 0;
mutex m;
ProgressBar* loadingBar; 

void SceneLoading()
{

	m.lock();
	Scene* tmp = new BaseScene1();
	SceneManager::Get()->Create("NewScene", tmp);
	SceneManager::Get()->Add("NewScene");
	initCount++;
	//loadingBar->SetAmount((float)initCount / 10.0f);
	//loadingBar->Update();
	//Environment::Get()->PostSet();
	//loadingBar->Render();

	Device::Get()->Clear();
	Environment::Get()->PostSet();
	loadingBar->SetAmount((float)initCount / 10.0f);
	loadingBar->Update();
	loadingScene->PostRender();
	Device::Get()->Present();

	tmp->Update();
	Sleep(500);
	initCount++;
	//loadingBar->SetAmount((float)initCount / 10.0f);
	//loadingBar->Update();
	//loadingBar->Render();
	Device::Get()->Clear();
	//loadingScene->Update();
	//loadingScene->PostRender();
	loadingBar->SetAmount((float)initCount / 10.0f);
	loadingBar->Update();
	loadingScene->PostRender();	
	Device::Get()->Present();
	Sleep(500);

	//tmp->PreRender();
	initCount++;
	//loadingBar->SetAmount((float)initCount / 10.0f);
	//loadingBar->Update();
	//loadingBar->Render();
	Device::Get()->Clear();
	//loadingScene->Update();
	//loadingScene->PostRender();
	loadingBar->SetAmount((float)initCount / 10.0f);
	loadingBar->Update();
	loadingScene->PostRender();
	Device::Get()->Present();
	Sleep(500);

	//tmp->Render();
	initCount++;
	//loadingBar->SetAmount((float)initCount / 10.0f);
	//loadingBar->Update();
	//loadingBar->Render();
	Device::Get()->Clear();
	//loadingScene->Update();
	//loadingScene->PostRender();
	loadingBar->SetAmount((float)initCount / 10.0f);
	loadingBar->Update();
	loadingScene->PostRender();
	Device::Get()->Present();
	Sleep(500);

	//tmp->PostRender();
	initCount++;
	//loadingBar->SetAmount((float)initCount / 10.0f);
	//loadingBar->Update();
	//loadingBar->Render();
	Device::Get()->Clear();
	//loadingScene->Update();
	//loadingScene->PostRender();
	loadingBar->SetAmount((float)initCount / 10.0f);
	loadingBar->Update();
	loadingScene->PostRender();
	Device::Get()->Present();

	m.unlock();

}


LoadingScene::LoadingScene()
{
	//titleBg = new Quad(Vector2(3840,2160));
	titleBg = new Quad(Vector2(1280, 720));

	titleBg->Pos() = middle;
	titleBg->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_title_BG.png");
	titleBg->UpdateWorld();

	title = new Quad(L"Textures/UI/T_Palworld_Logo_Small_White.png");
	title->Scale() *= 0.5f;
	title->Pos() = middle + Vector3(0.0f, 200.0f, 0.0f);

	loadingBar = new ProgressBar(L"Textures/Color/White.png",L"Textures/Color/WhiteGlass30.png");
	loadingBar->Pos() = middle + Vector3(0.0f,-300.0f,0.0f);
	loadingBar->Scale().x *= 4.0f;
	loadingBar->Scale().y *= 0.2f;

	title->UpdateWorld();

}

LoadingScene::~LoadingScene()
{
	th->join();
	delete th;
	delete titleBg;
	delete title;
	delete loadingBar;
}

void LoadingScene::Update()
{
	fakeT += DELTA;

	if (fakeT > RANDOM->Float(2.0f,3.0f) && initCount < 3)
	{
		initCount++;
		fakeT = 0.0f;
	}
	//else if(fakeT > RANDOM->Float(1.0f, 4.0f))
	//{
	//	initCount++;
	//	fakeT = 0.0f;
	//}
	if (fakeT > RANDOM->Float(1.0f, 4.0f) && initCount >= 8)
	{
		initCount++;
		fakeT = 0.0f;
	}




	if (!first && initCount == 3)
	{
		th = new thread(SceneLoading);
		first = true;
	}

	loadingBar->SetAmount((float)initCount/10.0f);
	loadingBar->Update();

	if(initCount == 10)
	{
		SceneManager::Get()->ChangeScene("NewScene");
		SceneManager::Get()->Remove("Loading");

		return;
	}
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
}

void LoadingScene::PostRender()
{
	titleBg->Render();
	title->Render();
	loadingBar->Render();
}

void LoadingScene::GUIRender()
{
	loadingBar->GUIRender();
}

