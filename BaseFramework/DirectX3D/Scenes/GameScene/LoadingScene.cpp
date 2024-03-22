#include "Framework.h"
#include "LoadingScene.h"
#include "Scenes/GameScene/BaseScene1.h"

int initCount = 0;
mutex m;

void SceneLoading()
{
	m.lock();
	Device::Get()->GetDeviceContext()->FinishCommandList(false, nullptr);
	SceneManager::Get()->Create("NewScene", new BaseScene1());

	m.unlock();

	m.lock();
	initCount++;
	m.unlock();
	//Sleep(1000);
	//
	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);
	//
	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);
	//
	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);
	//
	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);
	//
	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);

}


LoadingScene::LoadingScene()
{
	th = new thread(SceneLoading);
	big = new Quad(Vector2(500, 500));
	//SceneManager::Get()->Remove("Title");
}

LoadingScene::~LoadingScene()
{
	//th->join();
	//delete th;
	delete big;
}

void LoadingScene::Update()
{
	//if (initCount == 6)
	//{
	//	SceneManager::Get()->Add("NewScene");
	//	return;
	//}
	T += DELTA;
	//if (Ini)
	//{
	//	SceneManager::Get()->Create("NewScene", new BaseScene1());
	//	SceneManager::Get()->Add("NewScene");
	//	Ini = false;
	//}

	if(T>10.0f && initCount == 1)
	{
		th->join();
		SceneManager::Get()->ChangeScene("NewScene");
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
	big->Render();
}

void LoadingScene::GUIRender()
{
}

