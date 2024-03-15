#include "Framework.h"
#include "WorkBenchUI.h"

WorkBenchUI::WorkBenchUI()
{

	WorkBase = new Quad(Vector2(300, 300));
	WorkBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBase->Pos() = { WorkIconP.x,WorkIconP.y,0 };

	WorkBaseName = new Quad(Vector2(100, 50));
	WorkBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBaseName->Pos() = { WorkIconP.x,WorkIconP.y,0 };
	
	FOR(5)
	{
		MakeSlot[i] = new Quad(Vector2(50, 50));
		wstring file = L"Textures/UI/Make" + to_wstring(i) + L".png";
		MakeSlot[i]->GetMaterial()->SetDiffuseMap(file);
		MakeSlot[i]->Pos() = { WorkIconP + Vector3(i & 6, -i / 6, 0) * 60.0f };






	}
	


	
}

WorkBenchUI::~WorkBenchUI()
{


}

void WorkBenchUI::Update()
{



}

void WorkBenchUI::Render()
{
}

void WorkBenchUI::PostRender()
{
}

void WorkBenchUI::GUIRender()
{
}

void WorkBenchUI::MakeItem()
{
}


