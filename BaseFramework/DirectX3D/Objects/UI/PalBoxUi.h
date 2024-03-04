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
	//PalClickQuad* boxIcon[30];
	ClickQuad* boxIcon[5][6];

	Quad* partyBase;

	Quad* SlaveBase;
	ClickQuad* SlaveIcon[5];
};

