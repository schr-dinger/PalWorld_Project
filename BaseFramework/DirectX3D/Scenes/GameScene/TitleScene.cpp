#include "Framework.h"
#include "TitleScene.h"
#include "Scenes/GameScene/LoadingScene.h"
//#include "Scenes/GameScene/BaseScene1.h"

TitleScene::TitleScene()
{
	title = new Quad(Vector2(100,100));
}

TitleScene::~TitleScene()
{
	delete title;
}

void TitleScene::Update()
{
	if (KEY_DOWN('M'))
	{
		SceneManager::Get()->Create("Loading", new LoadingScene());
		SceneManager::Get()->Add("Loading");
		SceneManager::Get()->ChangeScene("Loading");

		//TitleScene::~TitleScene();
		return;
	}
}

void TitleScene::PreRender()
{
}

void TitleScene::Render()
{
}

void TitleScene::PostRender()
{
	title->Render();
}

void TitleScene::GUIRender()
{
}
