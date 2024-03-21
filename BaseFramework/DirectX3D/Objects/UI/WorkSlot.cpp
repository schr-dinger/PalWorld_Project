#include "Framework.h"
#include "WorkSlot.h"

WorkSlot::WorkSlot(int Number)
{

	test = Number;

	MakeSlot = new Quad(Vector2(50, 50));
	MakeSlotBase = new Quad(Vector2(50, 50));
		
	wstring file = L"Textures/UI/Make/Work" + to_wstring(test) + L".png";
	MakeSlot->GetMaterial()->SetDiffuseMap(file);

	MakeSlot->Update();
	MakeSlotBase->Update();


	// 스위치로 돌려서 필요한 아이템 수를 넣어서 돌려
	switch (test)
	{
	case 0:
		matter.resize(2);
		matter[0] = new WorkInFo(2, 2);
		matter[1] = new WorkInFo(1, 2);
		break;
		
	case 1:
		matter.resize(1);
		matter[0] = new WorkInFo(1, 4);
		break;
	case 2:
		matter.resize(1);
		matter[0] = new WorkInFo(2, 3);
		break;
	case 3:
		matter.resize(1);
		matter[0] = new WorkInFo(2, 1);
		break;
	case 4:
		matter.resize(1);
		matter[0] = new WorkInFo(1, 1);
		break;
	case 5:
		//matter = new WorkInFo(1, 3);
		break;
	default:

		break;

	}

	// 변수 하나 받아서 필요아이템 갯수만큼 테스트



}

WorkSlot::~WorkSlot()
{
	delete MakeSlot;
	delete MakeSlotBase;
	matter.clear();
	 


}

void WorkSlot::Update()
{
	if(CheckItem()) MakeSlotBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	else
	{
		MakeSlotBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedTest2.png");
		MakeSlotBase->GetMaterial()->GetData().emissive = { 0.5,0.5,0.5,0.5f };
	}

	MakeSlotBase->Update();
	MakeSlot->Update();
	
	FOR(matter.size())
	{
		matter[i]->SetPos(Vector3(MakeSlot->Pos().x+30, MakeSlot->Pos().y - (50 + i * 30.0f), 0));
		matter[i]->Update();
	}
	

	

}

void WorkSlot::Render()
{
	MakeSlotBase->Render();
	MakeSlot->Render();
	
	if (MouseCollision())
	{
		FOR(matter.size())
		{
			matter[i]->Render();
		}
	}

}

void WorkSlot::PostRender()
{
}

void WorkSlot::GUIRender()
{
	
	MakeSlotBase->GUIRender();
	

}

bool WorkSlot::MouseCollision()
{

	float minX = MakeSlot->Pos().x - MakeSlot->GetSize().x * 0.5f;
	float maxX = MakeSlot->Pos().x + MakeSlot->GetSize().x * 0.5f;
	float minY = MakeSlot->Pos().y - MakeSlot->GetSize().y * 0.5f;
	float maxY = MakeSlot->Pos().y + MakeSlot->GetSize().y * 0.5f;

	if (minX < mousePos.x && maxX > mousePos.x && minY < mousePos.y && maxY > mousePos.y)
	{
		return true;
	}

	return false;


	
}

bool WorkSlot::CheckItem()
{

	int check = 0;

	FOR(matter.size())
	{
		if (matter[i]->IsMakeOk()) check++;
	}
	

	if (check != 0 && check == matter.size()) return true;
	
	return false;
}

void WorkSlot::MakeItem()
{

	FOR(matter.size())
	{	
		ItemManager::Get()->GetItemDV()[matter[i]->GetNUM()].second -= matter[i]->GetCount();
		

	}
	ItemManager::Get()->MakeItem(test);
	
	



}
