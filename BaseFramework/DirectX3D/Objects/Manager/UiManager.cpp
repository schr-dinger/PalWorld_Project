#include "Framework.h"
#include "UiManager.h"

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
	palBoxUi->Update();
	buildUi->Update();
}

void UiManager::Render()
{
	palBoxUi->Render();
	//buildUi->Render();
}

void UiManager::PostRender()
{
	palBoxUi->PostRender();
	//buildUi->PostRender();
}

void UiManager::GuiRender()
{
	palBoxUi->GuiRender();
	buildUi->GuiRender();
}
