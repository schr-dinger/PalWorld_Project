#include "Framework.h"
#include "TitleScene.h"
#include "Scenes/GameScene/LoadingScene.h"
//#include "Scenes/GameScene/BaseScene1.h"

TitleScene::TitleScene()
{
	SOUND->Add("BGM_Title", "Sounds/UI/Title.wav", true, true);
	SOUND->Play("BGM_Title");

	//title = new Quad(Vector2(3840,2160)*0.4f);
	titleBg = new Quad(Vector2(1280,720));

	titleBg ->Pos() = middle;
	titleBg->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_title_BG.png");
	//SceneManager::Get()->Create("Loading", new LoadingScene());

	title = new Quad(L"Textures/UI/T_Palworld_Logo_Small_White.png");
	title->Scale() *= 0.5f;
	title->Pos() = middle + Vector3(0.0f, 200.0f, 0.0f);
	title->Rot().y = XM_PIDIV2;

	titleShadow = new Quad(L"Textures/UI/T_Title_logo_shadow.png");
	titleShadow->Scale() *= 1.0f;
	titleShadow->Pos() = middle + Vector3(0.0f, 200.0f, 0.0f);
	titleShadow->Rot().y = XM_PIDIV2;

	//FOR(2)
	//{
	//	blendState[i] = new BlendState();
	//}

	//blendState[1]->Alpha(true);
	//blendState[1]->AlphaToCoverage(true);


	titleBg->UpdateWorld();
	title->UpdateWorld();
	titleShadow->UpdateWorld();

}

TitleScene::~TitleScene()
{
	delete titleBg;
	delete title;
	delete titleShadow;

	//FOR(2) delete blendState[i];
}

void TitleScene::Update()
{
	if (title->Rot().y > 0.0f)
	{
		title->Rot().y -= DELTA*0.5f;
		titleShadow->Rot().y -= DELTA * 0.5f;
	}
	else
	{
		title->Rot().y = 0.0f;
		titleShadow->Rot().y = 0.0f;
		isGrowing = false;
	}


	if (!isGrowing && KEY_DOWN(VK_LBUTTON))
	{
		SOUND->Stop("BGM_Title");
		SceneManager::Get()->Create("Loading", new LoadingScene());
		SceneManager::Get()->ChangeScene("Loading");
		SceneManager::Get()->Remove("Title");

		return;
	}

	title->Update();
	titleShadow->Update();

}

void TitleScene::PreRender()
{
}

void TitleScene::Render()
{
}

void TitleScene::PostRender()
{
	titleBg->Render();
	//blendState[1]->SetState();
	if (isGrowing)
	{
		title->Render();
		titleShadow->Render();
	}
	else
	{
		title->Render();
	}
	//blendState[0]->SetState();
}

void TitleScene::GUIRender()
{
	titleShadow->GUIRender();
	//title -> GUIRender();
}
