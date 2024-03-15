#pragma once
class PalModeUi
{
public:
	PalModeUi();
	~PalModeUi();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

	void SetTexture();
private:
	Quad* baseDonut;
	Quad* donutPiece;
	float pieceRot;

	ClickQuad* selectA;
	ClickQuad* selectP;
	Quad* selectMiddle;



	Vector2 donutSize = { 600.0f,600.0f };
	Vector2 selectSize = { 150.0f,150.0f };

	Vector3 center = { 640.0f,360.0f,0.0f };

};

