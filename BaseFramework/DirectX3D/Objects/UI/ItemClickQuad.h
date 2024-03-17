#pragma once
class ItemClickQuad
{

public:
	ItemClickQuad();
	~ItemClickQuad();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();

	void SetTexture();
	void SetTem(class Item* item) { this->item = item; }

	bool MouseCollision();
	bool Check(int Num);
	bool Check2(int Num);


	Item* GetItem() { return item; }
	Quad* GetQuad() { return click; }
private:

	Quad* click;
	class Item* item;
	Vector2 size = { 50.0f,50.0f };
};










