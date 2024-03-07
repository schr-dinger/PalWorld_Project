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

	bool palBoxUiOn = false;
	bool buildUiOn = false;
	bool WorkBenchUiOn = false;


	bool buildPalBox = false;
	bool PlacedPalBox = false;

	bool buildWorkBench = false;
	bool PlacedWorkBench = false;
private:
	void ControlOn();


private:
	PalBoxUi* palBoxUi;
	BuildUi* buildUi;

	bool UiOn = false;

};

