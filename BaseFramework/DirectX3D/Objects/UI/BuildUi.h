#pragma once
class BuildUi
{
public:
	BuildUi();
	~BuildUi();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

	void SetTexture();
private:
	Quad* baseDonut;
	Quad* donutPiece;
	float pieceRot;

	ClickQuad* selectPalBox;

	ClickQuad* selectWorkBench;

	Quad* selectMiddle;

	Vector2 donutSize = {600.0f,600.0f};
	Vector2 selectSize = {150.0f,150.0f};

	Vector3 center = { 640.0f,360.0f,0.0f };

	// UI sound
	bool isPalBox = false;
	bool isWorkBench = false;

};

