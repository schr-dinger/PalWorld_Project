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

private:
	PalBoxUi* palBoxUi;
	BuildUi* buildUi;
};

