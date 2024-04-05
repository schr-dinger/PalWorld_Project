#include "Framework.h"
#include "TitleScene.h"
#include "Scenes/GameScene/LoadingScene.h"
//#include "Scenes/GameScene/BaseScene1.h"

Scene* loadingScene;

TitleScene::TitleScene()
{
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

	titleBg->UpdateWorld();
	title->UpdateWorld();
	titleShadow->UpdateWorld();

	gameStart = new ClickQuad(clickSize);
	gameStart->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	gameStart->GetQuad()->Pos() = middle + Vector3(0.0f, -50.0f, 0.0f);
	keySound[0] = true;

	gameExit = new ClickQuad(clickSize);
	gameExit->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
	gameExit->GetQuad()->Pos() = middle + Vector3(0.0f, -150.0f, 0.0f);
	keySound[1] = true;
	loadingScene = new LoadingScene();
	SceneManager::Get()->Create("Loading", loadingScene);
}

TitleScene::~TitleScene()
{
	delete titleBg;
	delete title;
	delete titleShadow;
	delete gameStart;
	delete gameExit;
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


	if (!isGrowing && gameStart->MouseCollision() && KEY_DOWN(VK_LBUTTON))
	{
		SOUND->Stop("BGM_Title");
		//loadingScene = new LoadingScene();
		//SceneManager::Get()->Create("Loading", loadingScene);
		SceneManager::Get()->ChangeScene("Loading");
		SceneManager::Get()->Remove("Title");

		return;
	}


	if (gameStart->MouseCollision() && !isGrowing)
	{
		if (keySound[0])
		{
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2", 0.7f);
		}
		gameStart->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
		keySound[0] = false;
	}
	else
	{
		gameStart->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
		keySound[0] = true;
	}

	if (gameExit->MouseCollision() && !isGrowing)
	{
		if (keySound[1])
		{
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2", 0.7f);
		}
		gameExit->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
		keySound[1] = false;
	}
	else
	{
		gameExit->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20.png");
		keySound[1] = true;
	}


	UiMouseManager::Get()->Update();

	title->Update();
	titleShadow->Update();
	gameStart->Update();
	gameExit->Update();
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
		gameStart->Render();
		gameExit->Render();

		{
			Font::Get()->SetStyle("FieldNum2");
			Font::Get()->RenderText("GAME START", { middle.x, middle.y - 30.0f }, 1);

			Font::Get()->SetStyle("FieldNum2");
			Font::Get()->RenderText("EXIT", { middle.x, middle.y -130.0f},1);

			Font::Get()->SetStyle("Default");
			Font::Get()->GetDC()->EndDraw();
			Font::Get()->GetDC()->BeginDraw();
		}

	}

	UiMouseManager::Get()->GetMouse()->Render();

	//blendState[0]->SetState();
}

void TitleScene::GUIRender()
{
	titleShadow->GUIRender();
	//title -> GUIRender();
}
