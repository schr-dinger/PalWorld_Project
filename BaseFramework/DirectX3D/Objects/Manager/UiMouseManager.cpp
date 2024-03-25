#include "Framework.h"
#include "UiMouseManager.h"

UiMouseManager::UiMouseManager()
{
	mouse = new Quad(L"Textures/Cursor/Cursor_default.png");
	mouse->Scale() *= 0.3f;

	crosshair = new Quad(L"Textures/UI/T_aim_test.png");
	crosshair->Scale() *= 0.125f;
	crosshair->Pos() = Vector3(640.0f, 360.0f, 0.0f);

	quad = new Quad(size);
	quadBack = new Quad(size);
	quadBack->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass20_C.png");
	tempPal = nullptr;

	crosshair->UpdateWorld();

	FOR(2) blendState[i] = new BlendState();
	blendState[1]->Alpha(true);
	//blendState[1]->AlphaToCoverage(true);
}

UiMouseManager::~UiMouseManager()
{
	delete mouse;
	delete quad;
	delete quadBack;
	delete crosshair;
}

void UiMouseManager::SetRender()
{
	if (tempPal != nullptr && tempItem == nullptr)
	{
		quadBack->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50_C.png");
		quad->GetMaterial()->SetDiffuseMap(tempPal->GetTextureC());
	}
	else if (tempItem != nullptr && tempPal == nullptr)
	{
		quadBack->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
		quad->GetMaterial()->SetDiffuseMap(tempItem->GetTexture());
	}
	else if (tempItem == nullptr && tempPal == nullptr)
	{
		quad->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	}
}

void UiMouseManager::Update()
{
	//cursor
	mouse->Pos() = mousePos + Vector3(20.0f, -20.0f, 0.0f);
	grabTimer += DELTA;

	switch (mstate)
	{
	case Mstate::D:
		mouse->GetMaterial()->SetDiffuseMap(L"Textures/Cursor/Cursor_default.png");
		if (KEY_PRESS(VK_LBUTTON))
		{
			mstate = Mstate::G;
		}
		break;

	case Mstate::G:
		mouse->GetMaterial()->SetDiffuseMap(L"Textures/Cursor/Cursor_grab.png");
		if (KEY_UP(VK_LBUTTON))
		{
			grabTimer = 0.0f;
			mstate = Mstate::L;
		}

		break;

	case Mstate::L:
		mouse->GetMaterial()->SetDiffuseMap(L"Textures/Cursor/Cursor_letgo.png");
		if (grabTimer > 0.2f)
		{
			mstate = Mstate::D;
		}
		break;
	}


	//cursor end
	mouse->Update();



	quad->Pos() = mousePos + Vector3(80,-50,0);
	quadBack->Pos() = mousePos + Vector3(80,-50,0);
	quad->UpdateWorld();
	quadBack->UpdateWorld();
}

void UiMouseManager::Render()
{
	blendState[1]->SetState();

	if (UiManager::Get()->GetUiOn())
	{
		mouse->Render();

	}
	else
	{
		crosshair->Render();
	}

	if (tempPal == nullptr &&tempItem == nullptr)
	{
		return;
	}
	else
	{
		SetRender();
		//blendState[1]->SetState();
		quadBack->Render();
		//blendState[0]->SetState();
		quad->Render();
	}
	blendState[0]->SetState();

}
