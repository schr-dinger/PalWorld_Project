#include "Framework.h"

UiManager::UiManager()
{
	palBoxUi = new PalBoxUi();
	buildUi = new BuildUi();
	partyUi = new PartyUi();
	fieldUI = new FieldUI();
	itemUi = new ItemUI();
}

UiManager::~UiManager()
{
	delete palBoxUi;
	delete buildUi;
	delete partyUi;
	delete fieldUI;
	delete itemUi;
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
		if (partyUiOn)
		{
			partyUi->ClearModel();
		}
		partyUiOn = !partyUiOn;
		partyUi->SetPal();
		
	}

	if (KEY_DOWN('U') && !palBoxUiOn && !partyUiOn)
	{
		InvenIsOn = !InvenIsOn;
		itemUi->SetItem();
	}


	if (palBoxUiOn)	palBoxUi->Update();
	if (buildUiOn) buildUi->Update();
	if (partyUiOn) partyUi->Update();
	if (InvenIsOn) itemUi->Update();
	fieldUI->Update();
}

void UiManager::Render()
{
	if (palBoxUiOn)	palBoxUi->Render();
	if (buildUiOn) buildUi->Render();
	if (partyUiOn) partyUi->Render();
	if (InvenIsOn) itemUi->Render();
}

void UiManager::PostRender()
{
	fieldUI->PostRender();
	if (palBoxUiOn)	palBoxUi->PostRender();
	if (buildUiOn)	buildUi->PostRender();
	if (partyUiOn) partyUi->PostRender();
	if (InvenIsOn) itemUi->PostRender();

}

void UiManager::GuiRender()
{
	fieldUI->GUIRender();
	//if (palBoxUiOn)	palBoxUi->GuiRender();
	//if (buildUiOn)	buildUi->GuiRender();
	if (partyUiOn) partyUi->GuiRender();
}

void UiManager::ControlOn()
{
	if (palBoxUiOn || buildUiOn || partyUiOn || InvenIsOn)
	{
		UiOn = true;
	}
	else
	{
		UiOn = false;
	}

	if (KEY_DOWN(VK_ESCAPE))
	{
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
		palBoxUiOn = false;
		buildUiOn = false;
		WorkBenchUiOn = false;
		partyUiOn = false;
		InvenIsOn = false;
	}
}
