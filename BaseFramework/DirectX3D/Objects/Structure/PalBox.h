#pragma once
class PalBox : public Model
{
public:
	PalBox(string name,Terrain* terrain);
	~PalBox();

	void Update();
	void Render();
	void GUIRender();

	void SetTerrain(Terrain* terrain);  //this->terrain = terrain; }

	void Place();
private:
	Terrain* terrain;
	BlendState* blendState[2];

};

