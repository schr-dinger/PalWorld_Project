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

};
