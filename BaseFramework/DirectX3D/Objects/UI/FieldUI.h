#pragma once
class FieldUI
{
public:
	FieldUI();
	~FieldUI();

	void Update();
	void PostRender();
	void GUIRender();
private:
	void SetPalUI();

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
	Quad* icon_B;

	// �� ������
	Quad* Pal1;
	Quad* Pal2;
	Quad* Pal3;
	Quad* PalQuad1;
	Quad* PalQuad2;
	Quad* PalQuad3;

	// ��UI ���ÿ�
	int selPal;

	// ��Ʈ
	Vector2 HpFontPos;
	Vector2 BuildFontPos;


	// ��Ʈ �׽�Ʈ��
	Vector2 fontPos;
	int maxHp;
	int curHp;


};

