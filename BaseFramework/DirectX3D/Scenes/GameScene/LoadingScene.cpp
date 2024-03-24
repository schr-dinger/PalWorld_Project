#include "Framework.h"
#include "LoadingScene.h"
#include "Scenes/GameScene/BaseScene1.h"

int initCount = 0;
mutex m;

void SceneLoading()
{

	m.lock();
	Scene* tmp = new BaseScene1();
	SceneManager::Get()->Create("NewScene", tmp);
	SceneManager::Get()->Add("NewScene");
	initCount++;
	tmp->Update();
	initCount++;
	tmp->PreRender();
	initCount++;
	tmp->Render();
	initCount++;
	tmp->PostRender();
	initCount++;
	m.unlock();


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
}

LoadingScene::~LoadingScene()
{
	th->join();
	delete th;
	delete pika;
}

void LoadingScene::Update()
{
	//if (!SceneManager::Get()->GetLoadingT()) return;

	if (!first)
	{
		th = new thread(SceneLoading);
		first = true;
	}


	//pika->Rot().z += 10* DELTA;
	//pika->Pos().x += 10* DELTA;
	pika->Scale().x *= initCount;
	pika->UpdateWorld();

	//T += DELTA;

	//if (T > 10.0f)
	if(initCount == 5)
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
	pika->Render();
}

void LoadingScene::GUIRender()
{
	ImGui::Text("Rot.z : %d", pika->Rot().z);
	ImGui::Text("Pos.x : %d", pika->Pos().x);
}

