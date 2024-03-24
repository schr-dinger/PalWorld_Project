#include "Framework.h"
#include "WorkInFo.h"

WorkInFo::WorkInFo(int num, int ItemC)
{

	NUM = num;
	Count = ItemC;

	MakeInFo = new Quad(Vector2(200, 30));
	InFoIcon = new Quad(Vector2(30, 30));


	switch (NUM)
	{
	case 1:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/Make/necessary0.png");
		break;
	case 2:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/Make/necessary1.png");
		break;
	default:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		break;
	}

	ItemCount = new Quad(Vector2(70, 30));



}

WorkInFo::~WorkInFo()
{
	delete MakeInFo;
	delete InFoIcon;
	delete ItemCount;

}

void WorkInFo::Update()
{

	MakeInFo->Pos() = InFoPos;
	InFoIcon->Pos() = Vector3(InFoPos.x - 50, InFoPos.y, 0);
	ItemCount->Pos() = Vector3(InFoPos.x + 130, InFoPos.y, 0);

	MakeInFo->Update();
	InFoIcon->Update();
	ItemCount->Update();



}

void WorkInFo::Render(int P_Count)
{


	MakeInFo->Render();
	InFoIcon->Render();
	ItemCount->Render();

	Font::Get()->SetStyle("FieldEquibName");
	switch (NUM)
	{
	case 1:
		Font::Get()->RenderText("³ª¹«", Vector2(InFoPos.x, InFoPos.y + 10));
		break;
	case 2:
		Font::Get()->RenderText("µ¹", Vector2(InFoPos.x + 10, InFoPos.y + 10));
		break;
	default:
		break;
	}

	Font::Get()->SetStyle("FieldPlay");
	int a = ItemManager::Get()->GetItemDV()[NUM].second;
	string b = to_string(a) + " / " + to_string(Count * P_Count);
	Font::Get()->RenderText(b, Vector2(InFoPos.x + 85, InFoPos.y + 10));
	Font::Get()->GetDC()->EndDraw();
	Font::Get()->GetDC()->BeginDraw();


}

void WorkInFo::PostRender()
{

}

void WorkInFo::GUIRender()
{
}

bool WorkInFo::IsMakeOk(int P_Count)
{

	if (ItemManager::Get()->GetItemDV()[NUM].second != 0 &&
		ItemManager::Get()->GetItemDV()[NUM].second >= Count * P_Count)
	{
		MakeInFo->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		ItemCount->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");

		return true;
	}


	MakeInFo->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedGlass80.png");
	ItemCount->GetMaterial()->SetDiffuseMap(L"Textures/Color/RedGlass50.png");

	return false;
}



