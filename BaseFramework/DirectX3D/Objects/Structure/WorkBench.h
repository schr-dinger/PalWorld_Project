#pragma once
class WorkBench
{
public:
	WorkBench();
	~WorkBench();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

	void Place(float x, float z);

	void Interaction();

	Transform* GetBuilding() { return building; }
	bool PalWorkCheck();

	//
	void SetCount(int count) { Count = count; }
	void SetItem(Item* item);
	Item* GetItem() { return WorkItem; }
	void BarUpdate();


private:
	Model* building;
	Model* finished;
	Transform* center;

	SphereCollider* range;
	SphereCollider* mouseHit;

	BlendState* blendState[2];

	FakeShadow* shadow;

	Model* cube;
	Vector3 off = { 13,0,13 };
	float off2 = 10.0f;
	LightBuffer::Light* light;

	bool Progressing = false;
	bool Done = false;

	bool isPlaced = false;

	float time = 1;
	float CompleteTime = 20;
	int Count = 0;

	Vector3 gaugePos;
	Item* WorkItem;
	ProgressBar* produceBar;


	Quad* test;


};

