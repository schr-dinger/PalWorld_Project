#pragma once
class PalClickQuad : public ClickQuad
{
public:
	PalClickQuad();
	~PalClickQuad();

	void SetTexture();


private:
	class Pal* pal;
	Vector2 size = {50.0f,50.0f};
};

