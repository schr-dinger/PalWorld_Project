#pragma once
class UiMouseManager :public Singleton<UiMouseManager>
{
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

private:
	Quad* quad;
	Quad* quadBack;
	Pal* tempPal;

	Vector2 size = { 70.0f,70.0f };
	int index;

};

