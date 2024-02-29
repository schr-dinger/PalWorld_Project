#pragma once
class PalBox
{
public:
	PalBox(Terrain* terrain);
	~PalBox();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

	void Place();
private:
	Terrain* terrain;

	Model* building;
	Model* finished;
	Transform* center;


	BlendState* blendState[2];

	Shadow* shadow;

	Model* cube;
	Vector3 off = { 13,0,13 };
	float off2 = 10.0f;
	LightBuffer::Light* light;

	bool isBuilding = false;
	bool Done = false;
};

