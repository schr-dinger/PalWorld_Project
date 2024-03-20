#pragma once
class ItemUI
{
public:
	ItemUI();
	~ItemUI();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();
	void SetItem();

	bool Check();
private:

private:

	Vector2 Screen = { 1280.0f,720.0f };

	Quad* invBase;
	Quad* invBaseName;

	Quad* EquipBase;
	Quad* EquipBaseName;

	Quad* woodIcon;
	Quad* stoneIcon;
	Quad* bowIcon;
	Quad* rifleIcon;

	//Quad* boxBaseName;
	//Vector2 boxBaseNameSize = { 490.0f,30.0f };

	Vector3 boxIconP = { 850.0f, 500.0f,0.0f };
	Vector3 EquipIconP = { 720.0f, 500.0f, 0.0f };

	ItemClickQuad* Slot[30];
	ItemClickQuad* SlotBase[30];

	ItemClickQuad* P_Equip[3];
	ItemClickQuad* P_EquipBase[3];

	// PalClickQuad* boxIconBase[30];

	vector<Quad*> TIcon;

	int select = 0;

};

