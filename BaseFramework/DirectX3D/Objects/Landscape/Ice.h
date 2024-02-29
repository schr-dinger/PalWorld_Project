#pragma once
class Ice : public Model
{
public:
	Ice(string name);
	~Ice();

	void Update();
	void Render();
	void GUIRender();


	void Attack();

private:
	BlendState* blendState[2];

};

