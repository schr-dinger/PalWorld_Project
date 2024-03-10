#include "Framework.h"

UiManager::UiManager()
{
	palBoxUi = new PalBoxUi();
	buildUi = new BuildUi();
	partyUi = new PartyUi();
}

UiManager::~UiManager()
{
	delete palBoxUi;
	delete buildUi;
	delete partyUi;
}

void UiManager::Update()
{
	ControlOn();

	if (KEY_DOWN('B') && !palBoxUiOn && !partyUiOn)
	{
		buildUiOn = !buildUiOn;
	}

	if (KEY_DOWN('P') && !palBoxUiOn && !buildUiOn)
	{
		partyUiOn = !partyUiOn;
	}



	palBoxUi->Update();
	buildUi->Update();
	partyUi->Update();
}

void UiManager::Render()
{
	if (palBoxUiOn)	palBoxUi->Render();
	if (buildUiOn) buildUi->Render();
	if (partyUiOn) partyUi->Render();
}

void UiManager::PostRender()
{
	if (palBoxUiOn)	palBoxUi->PostRender();
	if (buildUiOn)	buildUi->PostRender();
	if (partyUiOn) partyUi->PostRender();

}

void UiManager::GuiRender()
{
	if (palBoxUiOn)	palBoxUi->GuiRender();
	if (buildUiOn)	buildUi->GuiRender();
	if (partyUiOn) partyUi->GuiRender();

}

void UiManager::ControlOn()
{
	if (palBoxUiOn || buildUiOn || partyUiOn )
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
		partyUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}
}
