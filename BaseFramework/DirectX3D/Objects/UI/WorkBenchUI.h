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
	
	void MakeItem();
		
private:


private:

	Vector2 Screen = { 1280.0f,720.0f };
	Vector3 WorkIconP = { 400.0f, 400.0f,0.0f };


	Quad* WorkBase;
	Quad* WorkBaseName;

	WorkSlot* test[5];

	

	// �ʿ��� ������ 

	


	


};

