#include "Framework.h"
#include "WorkBenchUI.h"

WorkBenchUI::WorkBenchUI()
{

	WorkBase = new Quad(Vector2(350, 300));
	WorkBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBase->Pos() = { WorkIconP.x,WorkIconP.y,0 };

	WorkBaseName = new Quad(Vector2(100, 50));
	WorkBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBaseName->Pos() = { WorkIconP.x,WorkIconP.y+150,0 };
	
	FOR(5)
	{
		test[i] = new WorkSlot(i);
		test[i]->GetQuad()->Pos() = Vector3(WorkIconP.x + i * 60 - 120, WorkIconP.y + 100, 0);


		test[i]->GetBase()->Pos() = Vector3(WorkIconP.x + i * 60 - 120, WorkIconP.y + 100, 0);


	}
	
	WorkBase->Update();
	WorkBaseName->Update();

	

}

WorkBenchUI::~WorkBenchUI()
{


}

void WorkBenchUI::Update()
{

	FOR(5)
	{
		test[i]->Update();

	}


}

void WorkBenchUI::Render()
{
	
	WorkBaseName->Render();
	WorkBase->Render();

	FOR(5)
	{
		test[i]->Render();

	}


}

void WorkBenchUI::PostRender()
{
}

void WorkBenchUI::GUIRender()
{
}




