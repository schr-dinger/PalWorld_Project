#pragma once
#define MaxNum 2

class ItemManager : public Singleton<ItemManager>
{
private:


public:

	ItemManager();
	~ItemManager();


	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	void Mining(Item* item);
	void Equip();
	void MakeEquip(int EquipNum);

	// bool isCheck(int NUM);

	Item* GetItem(int NUM) { return items[NUM].back(); }

	vector<Item*>& GetWeaponV() { return weapons; }
	map<int, vector<Item*>>& GetItemV() { return items; }
	map<int, pair<int, int>>& GetItemDV() { return itemData; }

	void SetInvEquip(int NUM, Item* item) { invEquip[NUM] = item; }
	vector<Item*>& GetEquipV() { return invEquip; }

	// vector<Item*>& GetItemV() { return items; }


private:


	// vector<Item*> items;

	map<int, pair<int, int>> itemData;
	map<int, vector<Item*>> items;

	vector<Item*> weapons;

	vector<Item*> invEquip;



	// int 선택 

	// first 무슨 아이템인지 
	// second 갯수


};

