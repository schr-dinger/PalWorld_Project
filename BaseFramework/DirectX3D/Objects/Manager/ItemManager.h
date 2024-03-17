#pragma once
#define MaxMatter 2
#define MaxCunsum 3

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
	void MakeItem(int EquipNum);

	// bool isCheck(int NUM);

	Item* GetItem(int NUM) { return items[NUM].back(); }

	vector<Item*>& GetWeaponV() { return weapons; }
	map<int, vector<Item*>>& GetItemV() { return items; }
	map<int, pair<int, int>>& GetItemDV() { return itemData; }

	map<int, vector<Item*>>& GetConsumV() { return consumItems; }
	map<int, pair<int, int>>& GetConsumDV() { return consumData; }


	void SetInvEquip(int NUM, Item* item) { invEquip[NUM] = item; }
	vector<Item*>& GetEquipV() { return invEquip; }

	// vector<Item*>& GetItemV() { return items; }


private:


	// vector<Item*> items;

	map<int, pair<int, int>> itemData;
	map<int, vector<Item*>> items;

	map<int, pair<int, int>> consumData;
	map<int, vector<Item*>> consumItems;

	vector<Item*> weapons;
	vector<Item*> invEquip;



	// int 선택 

	// first 무슨 아이템인지 
	// second 갯수


};

