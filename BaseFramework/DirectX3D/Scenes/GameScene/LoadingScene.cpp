#include "Framework.h"
#include "LoadingScene.h"
#include "Scenes/GameScene/BaseScene1.h"

int initCount = 0;
mutex m;

void SceneLoading()
{

	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);

	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);

	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);

	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);

	//m.lock();
	//initCount++;
	//m.unlock();
	//Sleep(1000);


}


LoadingScene::LoadingScene()
{
	//pika = new Particle();
	pika = new Quad(Vector2(100, 100));
	SceneManager::Get()->Remove("Title");
	//th = new thread(SceneLoading);

}

LoadingScene::~LoadingScene()
{
	//th->join();
	//delete th;
	delete pika;
}

void LoadingScene::Update()
{
	if (!SceneManager::Get()->GetLoadingT()) return;

	pika->Rot().z += DELTA;

	T += DELTA;

	if (T > 10.0f)
	{
		SceneManager::Get()->ChangeScene("NewScene");
		return;
	}
	pika->Update();
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
}

void LoadingScene::PostRender()
{
	pika->Render();
}

void LoadingScene::GUIRender()
{
}

