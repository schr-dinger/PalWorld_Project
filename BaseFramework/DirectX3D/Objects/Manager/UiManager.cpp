#include "Framework.h"

UiManager::UiManager()
{
	palBoxUi = new PalBoxUi();
	buildUi = new BuildUi();
	partyUi = new PartyUi();
	fieldUI = new FieldUI();
	itemUi = new ItemUI();
	palModeUi = new PalModeUi();
	WorkBenUI = new WorkBenchUI();
}

UiManager::~UiManager()
{
	delete palBoxUi;
	delete buildUi;
	delete partyUi;
	delete fieldUI;
	delete itemUi;
	delete palModeUi;
	delete WorkBenUI;
}

void UiManager::Update()
{
	ControlOn();

	if (KEY_DOWN('B') && !palBoxUiOn && !partyUiOn && !palModeUiOn && !InvenIsOn)
	{
		buildUiOn = !buildUiOn;
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}

	if (KEY_DOWN('P') && !palBoxUiOn && !buildUiOn && !palModeUiOn && !InvenIsOn)
	{
		if (partyUiOn)
		{
			partyUi->ClearModel();
		}
		partyUiOn = !partyUiOn;
		partyUi->SetPal();
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}

	if (KEY_DOWN('U') &&!buildUiOn && !palBoxUiOn && !partyUiOn && !palModeUiOn)
	{
		InvenIsOn = !InvenIsOn;
		itemUi->SetItem();
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}

	if (KEY_DOWN('4') && !buildUiOn && !palBoxUiOn && !partyUiOn && !InvenIsOn)
	{
		palModeUiOn = !palModeUiOn;
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}




	if (palBoxUiOn)	palBoxUi->Update();
	if (buildUiOn) buildUi->Update();
	if (partyUiOn) partyUi->Update();
	if (InvenIsOn) itemUi->Update();
	if (palModeUiOn) palModeUi->Update();
	if (WorkBenchUiOn) WorkBenUI->Update();

	fieldUI->Update();

	UiMouseManager::Get()->Update();
}

void UiManager::Render()
{
	if (palBoxUiOn)	palBoxUi->Render();
	if (buildUiOn) buildUi->Render();
	if (partyUiOn) partyUi->Render();
	if (InvenIsOn) itemUi->Render();
	if (palModeUiOn) palModeUi->Render();
	if (WorkBenchUiOn) WorkBenUI->Render();

}

void UiManager::PostRender()
{
	fieldUI->PostRender();
	if (palBoxUiOn)	palBoxUi->PostRender();
	if (buildUiOn)	buildUi->PostRender();
	if (partyUiOn) partyUi->PostRender();
	if (InvenIsOn) itemUi->PostRender();
	if (palModeUiOn) palModeUi->PostRender();
	if (WorkBenchUiOn) WorkBenUI->PostRender();

	UiMouseManager::Get()->Render();

}

void UiManager::GuiRender()
{
	//fieldUI->GUIRender();
	//if (palBoxUiOn)	palBoxUi->GuiRender();
	//if (buildUiOn)	buildUi->GuiRender();
	if (partyUiOn) partyUi->GuiRender();
}

void UiManager::ControlOn()
{
	if (palBoxUiOn || buildUiOn || partyUiOn || InvenIsOn ||palModeUiOn || WorkBenchUiOn)
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
		palModeUiOn = false;
		WorkBenchUiOn = false;
	}
}
