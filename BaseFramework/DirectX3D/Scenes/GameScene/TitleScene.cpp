#include "Framework.h"
#include "TitleScene.h"
#include "Scenes/GameScene/LoadingScene.h"
//#include "Scenes/GameScene/BaseScene1.h"

TitleScene::TitleScene()
{
	//title = new Quad(Vector2(3840,2160)*0.4f);
	title = new Quad(Vector2(1280,720));

	title ->Pos() = { 1280.0f/2.0f,720.0f/2.0f ,0.0f};
	title->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_title_BG.png");
	//SceneManager::Get()->Create("Loading", new LoadingScene());
	title->UpdateWorld();

}

TitleScene::~TitleScene()
{
	delete title;
}

void TitleScene::Update()
{
	if (KEY_DOWN('M'))
	{
		//SceneManager::Get()->SetLoadingT(true);
		SceneManager::Get()->ChangeScene("Loading");
		SceneManager::Get()->Remove("Title");

		//SceneManager::Get()->ChangeScene("NewScene");
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
