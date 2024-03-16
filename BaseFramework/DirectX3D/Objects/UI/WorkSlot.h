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
			
	Quad* GetQuad() { return MakeSlot; }
	Quad* GetBase() { return MakeSlotBase; }

private:

	
	Quad* MakeSlot;
	Quad* MakeSlotBase;

	vector<WorkInFo*> matter;
	

	int test;




};