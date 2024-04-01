#pragma once
class WorkBenchUI
{

public:

	WorkBenchUI();
	~WorkBenchUI();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

private:


private:

	Vector2 Screen = { 1280.0f,720.0f };
	Vector3 WorkIconP = { 400.0f, 400.0f,0.0f };
	Vector3 SetIconP = { 400,325.0f,0.0f };

	Quad* WorkBase;
	Quad* WorkBaseName;

	WorkSlot* test[5];

	Quad* SetBase;
	ClickQuad* SetButton1;
	ClickQuad* SetButton2;

	int Count = 1;




};

