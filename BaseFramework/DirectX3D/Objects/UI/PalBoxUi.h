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

private:
	Quad* boxBase;
	Quad* boxBaseFrame;
	//PalClickQuad* boxIcon[30];
	ClickQuad* boxIcon[5][6];

	Quad* partyBase;

	Quad* SlaveBase;
	ClickQuad* SlaveIcon[5];

	Vector2 baseSize = { 1000.0f,500.0f };
};

