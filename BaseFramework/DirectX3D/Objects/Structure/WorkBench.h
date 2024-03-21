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

	void BarUpdate();

	void Place(float x, float z);

	void Interaction();
	void SetItem(Item* item);

private:
	Model* building;
	Model* finished;
	Transform* center;

	SphereCollider* range;
	SphereCollider* mouseHit;

	BlendState* blendState[2];

	FakeShadow* shadow;
	ProgressBar* produceBar;

	Model* cube;
	Vector3 off = { 13,0,13 };
	float off2 = 10.0f;
	LightBuffer::Light* light;

	bool Progressing = false;
	bool Done = false;

	bool isPlaced = false;

	// TEST

	bool testTime = false;
	float time = 1;
	float CompleteTime = 20;

	Vector3 gaugePos;
	Item* WorkItem;


};

