#pragma once
class UiMouseManager :public Singleton<UiMouseManager>
{
	enum class Mstate
	{
		D,
		G,
		L
	};

public:
	UiMouseManager();
	~UiMouseManager();

	void SetRender();

	void Update();
	void Render();


	void SetPal(Pal* pal) { this->tempPal = pal; }
	Pal* GetPal() { return tempPal; }
	void SetIndex(int index) { this->index = index; }
	int GetIndex() { return index; }

	void SetItem(Item* item) { this->tempItem = item; }
	Item* GetItem() { return tempItem; }
	Quad* GetMouse() { return mouse; }
private:
	Quad* mouse;
	Mstate mstate = Mstate::D;
	float grabTimer = 0.0f;

	Quad* crosshair;

	Quad* quad;
	Quad* quadBack;
	Pal* tempPal;
	Item* tempItem;

	Vector2 size = { 70.0f,70.0f };
	int index;

};

