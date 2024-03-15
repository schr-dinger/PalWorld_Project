#include "Framework.h"
#include "WorkInFo.h"

WorkInFo::WorkInFo(int num, int ItemC )
{

	NUM = num;
	
	MakeInFo = new Quad(Vector2(200, 50));
	
	MakeInFo->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	
	InFoIcon = new Quad(Vector2(50, 50));

		
	switch (NUM)
	{
	case 1:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/Make/necessary0");
		break;
	case 2:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/UI/Make/necessary1");
		break;
	default:
		InFoIcon->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		break;
	}
	
	ItemCount  = new Quad(Vector2(70, 50));
	ItemCount->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	
	
}

WorkInFo::~WorkInFo()
{
	
	delete MakeInFo;
	delete InFoIcon;
	delete ItemCount;
	

}

void WorkInFo::Update()
{
	InFoPos = mousePos + Vector3(50, -50,50);
	MakeInFo->Pos() = InFoPos;
	InFoIcon->Pos() = Vector3(InFoPos.x - 50, InFoPos.y, 0);
	ItemCount->Pos() = Vector3(InFoPos.x + 200, InFoPos.y, 0);
	

}

void WorkInFo::Render()
{


	MakeInFo->Render();
	InFoIcon->Render();
	ItemCount->Render();

	int a = ItemManager::Get()->GetItemDV()[NUM].second;
	string b = to_string(a);
	Font::Get()->RenderText(b, Vector2(InFoPos.x + 200, InFoPos.y));


}

void WorkInFo::PostRender()
{
}

void WorkInFo::GUIRender()
{
}

bool WorkInFo::IsMakeOk()
{

	if (ItemManager::Get()->GetItemDV()[NUM].second != 0 &&
		ItemManager::Get()->GetItemDV()[NUM].second >= NUM)
	{
		return true;
	}

	return false;
}



