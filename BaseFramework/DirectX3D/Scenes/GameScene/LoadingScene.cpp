#include "Framework.h"
#include "LoadingScene.h"

int initCount = 0;
mutex m;

LoadingScene::LoadingScene()
{
	th = new thread();
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update()
{
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
}

void LoadingScene::PostRender()
{
}

void LoadingScene::GUIRender()
{
}

void LoadingScene::SceneLoading()
{

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

	m.lock();
	initCount++;
	m.unlock();
	Sleep(1000);

}
