#include "Framework.h"
#include "WorkSlot.h"

WorkSlot::WorkSlot(int Number)
{

	NUM = Number;

	MakeSlot = new Quad(Vector2(50, 50));
	MakeSlotBase = new ClickQuad(Vector2(50, 50));

	wstring file = L"Textures/UI/Make/Work" + to_wstring(NUM) + L".png";
	MakeSlot->GetMaterial()->SetDiffuseMap(file);

	MakeSlot->Update();
	MakeSlotBase->Update();


	// 스위치로 돌려서 필요한 아이템 수를 넣어서 돌려
	switch (NUM)
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

	if (CheckItem() && !MakeSlotBase->MouseCollision()) MakeSlotBase->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png"), Sound_C = false;
	else if (MakeSlotBase->MouseCollision())
	{
		if(CheckItem()) MakeSlotBase->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlueGlass.png");
		else MakeSlotBase->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedGlass80.png");
		if (!Sound_C)
		{
			SOUND->Stop("UI_2"), SOUND->Play("UI_2", 0.7f);
			Sound_C = true;
		}
	}
	else
	{
		MakeSlotBase->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedGlass80.png");
		Sound_C = false;
	}

	MakeSlotBase->Update();
	MakeSlot->Update();

	FOR(matter.size())
	{
		matter[i]->SetPos(Vector3(MakeSlot->Pos().x + 30, MakeSlot->Pos().y - (50 + i * 30.0f), 0));
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
			matter[i]->Render(Count);
		}
	}

}

void WorkSlot::PostRender()
{
}

void WorkSlot::GUIRender()
{

	


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
		if (matter[i]->IsMakeOk(Count)) check++;
	}


	if (check != 0 && check == matter.size()) return true;

	return false;
}

void WorkSlot::MakeItem(int Count)
{

	FOR(matter.size())
	{
		ItemManager::Get()->GetItemDV()[matter[i]->GetNUM()].second -= matter[i]->GetCount() * Count;

	}

	StructureManager::Get()->GetWorkBench()->SetCount(Count);
	ItemManager::Get()->MakeItem(NUM);





}
