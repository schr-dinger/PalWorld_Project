#pragma once
class PalBox
{
public:
	PalBox(Terrain* terrain);
	~PalBox();

	void Update();
	void Render();
	void GUIRender();

	void SetTerrain(Terrain* terrain);  //this->terrain = terrain; }

	void Place();
private:
	Terrain* terrain;

	Model* building;
	Model* finished;

	BlendState* blendState[2];

};

