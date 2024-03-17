#include "Framework.h"
#include "ItemUI.h"

ItemUI::ItemUI()
{


	invBase = new Quad(Vector2(400, 420));
	invBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	invBase->Pos() = { boxIconP.x + 150,boxIconP.y - 100,0 };

	invBaseName = new Quad(Vector2(100, 50));
	invBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	invBaseName->Pos() = { boxIconP.x + 50, boxIconP.y + 75 };

	EquipBase = new Quad(Vector2(150, 400));
	EquipBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	EquipBase->Pos() = { 720, 400,0 };

	EquipBaseName = new Quad(Vector2(100, 50));
	EquipBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	EquipBaseName->Pos() = { 720,570,0 };

	invBase->Update();
	invBaseName->Update();

	EquipBase->Update();
	EquipBaseName->Update();

	FOR(3)
	{
		P_Equip[i] = new ItemClickQuad();
		P_Equip[i]->GetQuad()->Pos() = EquipIconP + Vector3(0, -i * 60.0f, 0);
		P_EquipBase[i] = new ItemClickQuad();
		P_EquipBase[i]->GetQuad()->Pos() = EquipIconP + Vector3(0, -i * 60.0f, 0);


	}

	FOR(30)
	{
		Slot[i] = new ItemClickQuad();
		Slot[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0) * 60.0f;
		SlotBase[i] = new ItemClickQuad();
		SlotBase[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0) * 60.0f;

	}



}

ItemUI::~ItemUI()
{
	delete invBase;
	delete invBaseName;

	delete EquipBase;
	delete EquipBaseName;


	FOR(30)
	{
		delete Slot[i];
		delete SlotBase[i];
	}
	FOR(3)
	{
		delete P_Equip[i];
		delete P_EquipBase[i];
	}


}

void ItemUI::Update()
{




	FOR(30)
	{
		Slot[i]->SetTexture();

		if (Slot[i]->GetItem() != nullptr && Slot[i]->MouseCollision() && Slot[i]->GetItem()->type == Item::Type::WEAPON && KEY_DOWN('H'))
		{
			for (int j = 0; j < 3; j++)
			{
				if (P_Equip[j]->GetItem() == nullptr)
				{
					P_Equip[j]->SetTem(Slot[i]->GetItem());
					Slot[i]->SetTem(nullptr);
				}

			}

		}



		if (Slot[i]->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetItem() == nullptr)
		{
			UiMouseManager::Get()->SetItem(Slot[i]->GetItem());
			UiMouseManager::Get()->SetIndex(i);
			//Slot[i]->SetTem(nullptr);
		}
		if (Slot[i]->MouseCollision() && KEY_UP(VK_LBUTTON) && UiMouseManager::Get()->GetItem() != nullptr)
		{

			int tmp = UiMouseManager::Get()->GetIndex();
			Item* palTmp = Slot[i]->GetItem();
			Slot[i]->SetTem(Slot[tmp]->GetItem());
			Slot[tmp]->SetTem(palTmp);
			SetItem();

			UiMouseManager::Get()->SetItem(nullptr);

		}


		if (SlotBase[i]->MouseCollision())
		{
			SlotBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
		}
		else
		{
			//boxIconBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
			SlotBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");

		}



		Slot[i]->Update();
		SlotBase[i]->Update();

	}

	FOR(3)
	{
		P_Equip[i]->SetTexture();

		if (P_Equip[i]->GetItem() != nullptr && P_Equip[i]->MouseCollision() && KEY_DOWN('H'))
		{
			for (int j = 0; j < 30; j++)
			{
				if (Slot[j]->GetItem() == nullptr)
				{
					Slot[j]->SetTem(P_Equip[i]->GetItem());
					P_Equip[i]->SetTem(nullptr);
					break;
				}
			}
		}


		if (P_EquipBase[i]->MouseCollision())
		{
			P_EquipBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
		}
		else
		{
			P_EquipBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
		}


		P_Equip[i]->Update();
		P_EquipBase[i]->Update();

		if (P_Equip[i]->GetItem() != nullptr)
		{

			ItemManager::Get()->SetInvEquip(i, P_Equip[i]->GetItem());

		}
		else
		{
			ItemManager::Get()->SetInvEquip(i, nullptr);
		}

	}

	UiMouseManager::Get()->Update();



}

void ItemUI::Render()
{
}

void ItemUI::PostRender()
{


	invBase->Render();
	invBaseName->Render();

	EquipBase->Render();
	EquipBaseName->Render();

	FOR(30)
	{
		SlotBase[i]->Render();
		Slot[i]->Render();


	}
	FOR(3)
	{
		P_EquipBase[i]->Render();
		P_Equip[i]->Render();
	}


	UiMouseManager::Get()->Render();

	{



		Font::Get()->SetStyle("invBaseName");
		Font::Get()->RenderText("인벤토리", { boxIconP.x + 15,boxIconP.y + 90 });


		Font::Get()->SetStyle("EquipBaseName");
		Font::Get()->RenderText("장비", { 700,585 });

		Font::Get()->SetStyle("Default");
		Font::Get()->GetDC()->EndDraw();
		Font::Get()->GetDC()->BeginDraw();

	}




}

void ItemUI::GUIRender()
{

}

void ItemUI::SetItem()
{

	FOR(30)
	{

		if (!ItemManager::Get()->GetWeaponV().empty() && Slot[i]->GetItem() == nullptr)
		{
			Slot[i]->SetTem(ItemManager::Get()->GetWeaponV().back());
			ItemManager::Get()->GetWeaponV().pop_back();
		}


		for (int r = 0; r < MaxCunsum; r++)
		{


			if (!ItemManager::Get()->GetConsumV()[r].empty() && Slot[i]->GetItem() == nullptr)
			{
				bool test2 = false;

				for (int t = 0; t < 30; t++)
				{
					if (Slot[t]->GetItem() != nullptr && Slot[t]->Check2(r))
					{
						test2 = true;
						break;
					}
				}


				if (!test2)
				{
					Item* testyo = new Consumable(r + 1);
					Slot[i]->SetTem(testyo);

				}



			}
			//else if (ItemManager::Get()->GetItemV()[j].empty() && Slot[i]->GetItem()->type == ItemManager::Get()->GetItemV()[j])
		}


		for (int j = 0; j < MaxMatter; j++)
		{


			if (!ItemManager::Get()->GetItemV()[j].empty() && Slot[i]->GetItem() == nullptr)
			{
				bool test = false;

				for (int k = 0; k < 30; k++)
				{
					if (Slot[k]->GetItem() != nullptr && Slot[k]->Check(j))
					{
						test = true;
						break;
					}
				}


				if (!test)
				{
					Item* testDa = new Ingredient(j + 1);
					Slot[i]->SetTem(testDa);

				}



			}
			//else if (ItemManager::Get()->GetItemV()[j].empty() && Slot[i]->GetItem()->type == ItemManager::Get()->GetItemV()[j])

		}





	}


}


