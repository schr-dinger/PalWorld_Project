#pragma once
class UiManager :public Singleton<UiManager>
{
public:
	UiManager();
	~UiManager();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

	bool GetUiOn() { return UiOn; }

	void SetPalBoxUI() { palBoxUi->SetPal(); }

	bool palBoxUiOn = false;
	bool buildUiOn = false;
	bool WorkBenchUiOn = false;
	bool partyUiOn = false;
	bool palModeUiOn = false;

	bool buildPalBox = false;
	bool PlacedPalBox = false;

	bool buildWorkBench = false;
	bool PlacedWorkBench = false;


	bool InvenIsOn = false;
private:
	void ControlOn();


private:
	PalBoxUi* palBoxUi;
	BuildUi* buildUi;
	PartyUi* partyUi;
	FieldUI* fieldUI;
	ItemUI* itemUi;
	PalModeUi* palModeUi;

	bool UiOn = false;


	//
	WorkBenchUI* WorkBenUI;

};

