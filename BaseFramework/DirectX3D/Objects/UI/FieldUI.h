#pragma once
class FieldUI
{
public:
	FieldUI();
	~FieldUI();

	void Update();
	void PostRender();
	void GUIRender();

	void SetPalUI(); // 팰박스에서 바뀔시 세팅

private:
	//void SetPalUI();

private:
	// 플레이어 체력 배고픔 바
	ProgressBar* hpBar;
	ProgressBar* hgyBar;
	// 그 왼쪽에 있는 체력, 배고픔 아이콘
	Quad* hpQuad;
	Quad* hgyQuad;

	// 키 아이콘
	Quad* icon_1;
	Quad* icon_2;
	Quad* icon_3;
	Quad* icon_Q;
	Quad* icon_E;
	Quad* icon_B;

	// 팔 아이콘
	Quad* Pal1;
	Quad* Pal2;
	Quad* Pal3;
	Quad* PalQuad1;
	Quad* PalQuad2;
	Quad* PalQuad3;

	// 팔UI 선택용
	int selPal;
	Quad* selPalQuad;
	ProgressBar* selPalHpBar;

	// 플레이어 장비
	Quad* palSpearBaseQuad;
	Quad* palSpearTextQuad;
	Quad* palSpearRenderQuad;
	Quad* palSpearIcon;

	Quad* equipBaseQuad;
	Quad* equipTextQuad;
	Quad* equipRenderQuad;
	Quad* equipIcon;
	Quad* equipSlash; // 공간 나누는 쿼드, 왼쪽 장비 그림, 오른쪽 투사체 개수


	// 폰트 위치
	Vector2 HpFontPos;
	Vector2 BuildFontPos;
	Vector2 selPalLvFontPos;
	Vector2 selPalLvNumFontPos;
	Vector2 selPalNameFontPos;


	// 폰트 테스트용
	Vector2 fontPos;
	int maxHp;
	int curHp;


};

