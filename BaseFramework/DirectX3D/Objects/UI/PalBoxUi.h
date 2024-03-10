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
	Vector2 baseBoxSize = { 500.0f,360.0f };

	Quad* boxBaseName;
	Vector2 boxBaseNameSize = { 490.0f,30.0f };


	Vector3 boxIconP = { 490.0f, 500.0f,0.0f };
	PalClickQuad* boxIcon[30];
	PalClickQuad* boxIconBase[30];


	Quad* partyBase;
	Vector2 partyBaseSize = { 300.0f,425.0f };

	Quad* partyBaseName;
	Vector2 partyBaseNameSize = { 290.0f,30.0f };

	Vector3 partyIconP = { 235.0f, 500.0f,0.0f };
	PartyBox* partyIcon[5];

	Quad* SlaveBase;
	ClickQuad* SlaveIcon[5];


};

