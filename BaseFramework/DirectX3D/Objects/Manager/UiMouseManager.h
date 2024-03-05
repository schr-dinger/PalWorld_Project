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

private:
	Quad* quad;
	Pal* tempPal;
	Vector2 size = { 100.0f,100.0f };

};

