#include "Framework.h"

UiManager::UiManager()
{
	palBoxUi = new PalBoxUi();
	buildUi = new BuildUi();
}

UiManager::~UiManager()
{
	delete palBoxUi;
	delete buildUi;
}

void UiManager::Update()
{
	ControlOn();

	if (KEY_DOWN('B') && !palBoxUiOn)
	{
		buildUiOn = !buildUiOn;
	}



	if (palBoxUiOn)
	{
		palBoxUi->Update();
	}
	//palBoxUi->Update();

	if (buildUiOn) buildUi->Update();

	//buildUi->Update();
}

void UiManager::Render()
{
	if (palBoxUiOn)	palBoxUi->Render();
	if (buildUiOn) buildUi->Render();
}

void UiManager::PostRender()
{
	if (palBoxUiOn)	palBoxUi->PostRender();
	if (buildUiOn)	buildUi->PostRender();
}

void UiManager::GuiRender()
{
	palBoxUi->GuiRender();
	buildUi->GuiRender();
}

void UiManager::SetUI()
{
	palBoxUi->SetPal();

}

void UiManager::ControlOn()
{
	if (palBoxUiOn || buildUiOn)
	{
		UiOn = true;
	}
	else
	{
		UiOn = false;
	}

	if (KEY_DOWN(VK_ESCAPE))
	{
		palBoxUiOn = false;
		buildUiOn = false;
		WorkBenchUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}
}
