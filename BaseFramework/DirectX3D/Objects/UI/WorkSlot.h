#pragma once
class WorkSlot
{

public:

	WorkSlot(int Number);
	~WorkSlot();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	bool MouseCollision();
	bool CheckItem();
			
	void MakeItem(int Count =1);
	void SetCount(int count) { Count = count; }

	Quad* GetQuad() { return MakeSlot; }
	Quad* GetBase() { return MakeSlotBase; }

	int GetNum() { return NUM; }

private:

	
	Quad* MakeSlot;
	Quad* MakeSlotBase;

	vector<WorkInFo*> matter;
	
	int NUM;
	int Count = 1;
	


};