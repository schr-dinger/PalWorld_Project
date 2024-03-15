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

private:

	Vector3 TestPos = { 400,400,0 };

	Quad* MakeSlot;

	WorkInFo* test;
	WorkInFo* test2;






};