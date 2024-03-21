#pragma once
class WorkInFo
{

public:

	WorkInFo(int num, int ItemC);
	~WorkInFo();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	bool IsMakeOk();

	void SetPos(Vector3 Pos) { InFoPos = Pos; }

	int GetCount() { return Count; }
	int GetNUM() { return NUM; }
private:


private:

	// 필요한 아이템 

	Vector3 InFoPos = { 0.0f,0.0f,0.0f };

	Quad* MakeInFo;  // 들어가는 아이템의 창 
	Quad* InFoIcon;  // 들어가는 아이템..
	Quad* ItemCount; // 들어가는 아이템 갯수..

	int NUM = 0;
	int Count = 0;


};

