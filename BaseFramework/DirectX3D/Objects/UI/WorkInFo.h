#pragma once
class WorkInFo
{

public:

	WorkInFo(int num,int ItemC);
	~WorkInFo();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();
			 
	bool IsMakeOk();
	
	void SetPos(Vector3 Pos) { InFoPos = Pos; }
private:


private:
	
	// �ʿ��� ������ 
			
	Vector3 InFoPos = { 0.0f,0.0f,0.0f };

	Quad* MakeInFo;  // ���� �������� â 
	Quad* InFoIcon;  // ���� ������..
	Quad* ItemCount; // ���� ������ ����..
		
	int NUM = 0;

};

