#pragma once
class PartyBox
{
private:
	//enum class PickState
	//{
	//	RELEASE,
	//	PICKING
	//};

public:
	PartyBox();
	~PartyBox();

	void Update();
	//void Render();
	void PostRender();
	void GUIRender();

	bool MouseCollision();

	void SetPal(Pal* pal) { this->pal = pal; }
	Pal* GetPal() { return pal; }

	Quad* GetQuad() { return partyBox1; }
	void SetTexture3();

private:
	Quad* partyBox1;
	//Quad* partyBox2;
	Quad* partyBox3;
	//Quad* partyBox4;
	class Pal* pal;

	//PickState pickState;

	ProgressBar* hpBar;
	ProgressBar* hgyBar;

	Vector2 fontLvNumPos;
	Vector2 fontLvPos;
	Vector2 fontNamePos;


	// 폰트 테스트용
	Vector2 fontPos;

};

