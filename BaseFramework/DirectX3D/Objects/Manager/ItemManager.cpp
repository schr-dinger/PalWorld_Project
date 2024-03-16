#include "Framework.h"

ItemManager::ItemManager()
{


	weapons.resize(30);
	invEquip.resize(4);
	/*
	FOR(MaxNum)
	{
		items[i].resize(30);
	}

	*/

	


}

ItemManager::~ItemManager()
{
	weapons.clear();
	invEquip.clear();
	for (auto& pair : items)
	{

		for (auto item : pair.second)
		{
			delete item;
		}
		pair.second.clear();

	}
}

void ItemManager::Update()
{

	FOR(invEquip.size())
	{
		if (invEquip[i] != nullptr) PlayerManager::Get()->GetPlayer()->SetModel(i, invEquip[i]->GetModel());
		else PlayerManager::Get()->GetPlayer()->SetModel(i, nullptr);

	}

}

void ItemManager::Render()
{



}

void ItemManager::PostRender()
{



}


void ItemManager::Mining(Item* item)
{

	if (item == nullptr)
		return;


	if (item->type == Item::Type::INGREDIENT)
	{


		if (itemData[item->num].second == 0)
		{
			itemData[item->num].first = item->num;
			itemData[item->num].second++;
		}
		else
		{
			for (auto& data : itemData)
			{
				if (data.second.first == item->num)
				{
					data.second.second++;
					break;
				}
			}
		}
		items[item->num - 1].push_back(item);
	}
	else if (item->type == Item::Type::WEAPON)
	{

		weapons.push_back(item);


	}

}

void ItemManager::MakeEquip(int EquipNum)
{







}



