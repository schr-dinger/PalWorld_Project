#pragma once
class PalClickQuad
{
public:
	PalClickQuad();
	~PalClickQuad();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

	void SetTexture();
	void SetPal(class Pal* pal) { this->pal =pal; }

	bool MouseCollision();

	Pal* GetPal() { return pal; }
	Quad* GetQuad() { return click; }
private:

	Quad* click;
	class Pal* pal;
	Vector2 size = {50.0f,50.0f};
};

