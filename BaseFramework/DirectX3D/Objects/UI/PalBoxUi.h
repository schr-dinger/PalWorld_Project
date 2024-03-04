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
	Quad* boxIcon[30];

	Quad* partyBase;

	Quad* SlaveBase;
	Quad* SlaveIcon[5];
};

