#pragma once
class PalClickQuad : public ClickQuad
{
public:
	PalClickQuad();
	~PalClickQuad();

	void SetTexture();
	void SetPal(class Pal* pal) { this->pal =pal; }
	Pal* GetPal() { return pal; }

private:
	class Pal* pal;
	Vector2 size = {50.0f,50.0f};
};

