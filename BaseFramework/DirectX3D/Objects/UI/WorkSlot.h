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
			
	void MakeItem();

	Quad* GetQuad() { return MakeSlot; }
	Quad* GetBase() { return MakeSlotBase; }

	int GetNum() { return test; }

private:

	
	Quad* MakeSlot;
	Quad* MakeSlotBase;

	vector<WorkInFo*> matter;
	
	int test;

	


};