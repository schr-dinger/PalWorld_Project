#pragma once
class FieldUI
{
public:
	FieldUI();
	~FieldUI();

	void Update();
	void PostRender();
	void GUIRender();

	void SetPalUI(); // �ӹڽ����� �ٲ�� ����

private:
	//void SetPalUI();

private:
	// �÷��̾� ü�� ����� ��
	ProgressBar* hpBar;
	ProgressBar* hgyBar;
	// �� ���ʿ� �ִ� ü��, ����� ������
	Quad* hpQuad;
	Quad* hgyQuad;

	// Ű ������
	Quad* icon_1;
	Quad* icon_2;
	Quad* icon_3;
	Quad* icon_Q;
	Quad* icon_E;
	Quad* icon_E2;
	Quad* icon_B;
	Quad* icon_MW;
	Quad* icon_Swap1;
	Quad* icon_Swap2;

	// �� ������
	Quad* Pal1;
	Quad* Pal2;
	Quad* Pal3;
	Quad* PalQuad1;
	Quad* PalQuad2;
	Quad* PalQuad3;

	// ��UI ���ÿ�
	int selPal;
	Quad* selPalQuad;
	ProgressBar* selPalHpBar;

	// �÷��̾� ���
	Quad* palSpearTextQuad;
	Quad* palSpearRenderQuad;
	Quad* palSpearIcon;

	Quad* equipTextQuad;
	Quad* equipRenderQuad;
	Quad* equipIcon;
	Quad* equipSlash; // ���� ������ ����, ���� ��� �׸�, ������ ����ü ����

	// �÷��� ���� �ȳ�
	Quad* pressBQuad;
	Quad* pressEQuad;
	Quad* pressQQuad;

	// ��Ʈ ��ġ
	Vector2 HpFontPos;
	Vector2 BuildFontPos;
	Vector2 selPalLvFontPos;
	Vector2 selPalLvNumFontPos;
	Vector2 selPalNameFontPos;
	Vector3 palSpearTextFontPos;
	Vector3 equipTextFontPos;
	Vector2 pressBFontPos;
	Vector2 pressEFontPos;
	Vector2 pressQFontPos;
	Vector2 parSpear100FontPos;
	Vector2 parSpear010FontPos;
	Vector2 parSpear001FontPos;
	Vector2 ProjLoadNumFontPos;
	Vector2 ProjTotalNumFontPos;



	// �׽�Ʈ��
	Vector2 fontPos;
	int maxHp;
	int curHp;
	int tmpPalSpear;

};

