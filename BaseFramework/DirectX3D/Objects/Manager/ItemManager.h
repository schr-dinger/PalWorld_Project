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

	map<int, pair<int, int>>& GetBulletDV() { return BulletData; }

	void SetInvEquip(int NUM, Item* item) { invEquip[NUM] = item; }
	vector<Item*>& GetEquipV() { return invEquip; }
	string GetEquipVN(int NUM);
	
	// vector<Item*>& GetItemV() { return items; }


private:


	// vector<Item*> items;

	map<int, pair<int, int>> itemData;
	map<int, vector<Item*>> items;

	map<int, pair<int, int>> consumData;
	map<int, vector<Item*>> consumItems;

	vector<Item*> weapons;
	vector<Item*> invEquip;

	map<int, pair<int, int>> BulletData;

	// int ���� 

	// first ���� ���������� 
	// second ����


};

