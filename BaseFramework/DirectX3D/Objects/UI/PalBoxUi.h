#pragma once
class PalBoxUi
{
public:
	PalBoxUi();
	~PalBoxUi();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

private:
	void SetPal();
private:

	Vector2 Screen = { 1280.0f,720.0f };
	Quad* boxBase;

	Vector3 boxIconP = { 490.0f, 500.0f,0.0f };
	PalClickQuad* boxIcon[30];
	PalClickQuad* boxIconBase[30];


	Quad* partyBase;

	Quad* SlaveBase;
	ClickQuad* SlaveIcon[5];

	Vector2 baseBoxSize = { 500.0f,360.0f };
	//Vector2 basePartySize = {}
	bool UiOn = false;
};

