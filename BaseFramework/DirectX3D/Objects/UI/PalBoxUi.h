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
	Vector2 Screen = { 1280.0f,720.0f };
	Quad* boxBase;

	Vector3 boxIconP = { 0.0f, 720.0f,0.0f };
	ClickQuad* boxIcon[30];

	Quad* partyBase;

	Quad* SlaveBase;
	ClickQuad* SlaveIcon[5];

	Vector2 baseSize = { 500.0f,360.0f };
};

