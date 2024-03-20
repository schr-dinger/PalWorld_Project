#include "Framework.h"
#include "WorkBenchUI.h"

WorkBenchUI::WorkBenchUI()
{

	WorkBase = new Quad(Vector2(350, 300));
	WorkBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBase->Pos() = { WorkIconP.x,WorkIconP.y,0 };

	WorkBaseName = new Quad(Vector2(100, 50));
	WorkBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	WorkBaseName->Pos() = { WorkIconP.x,WorkIconP.y + 150,0 };

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
	delete WorkBase;
	delete WorkBaseName;
	FOR(5)
	{
		delete test[i];
	}


}

void WorkBenchUI::Update()
{

	FOR(5)
	{
		if (test[i]->CheckItem() && test[i]->MouseCollision() && KEY_DOWN('J'))
		{
			// 다른 곳으로 추가?
			test[i]->MakeItem();
		}
		test[i]->Update();


	}


}

void WorkBenchUI::Render()
{




}

void WorkBenchUI::PostRender()
{
	WorkBaseName->Render();
	WorkBase->Render();

	FOR(5)
	{
		test[i]->Render();

	}

	Font::Get()->RenderText(" 작업대 ", { WorkIconP.x - 30,WorkIconP.y + 160 });


	//string a = to_string(ItemManager::Get()->GetConsumV()[0].size());
	//string b = to_string(ItemManager::Get()->GetConsumV()[1].size());
	//string c = to_string(ItemManager::Get()->GetConsumV()[2].size());
	//	
	//Font::Get()->RenderText(a, { WorkIconP.x + 30,WorkIconP.y + 160 });
	//Font::Get()->RenderText(b, { WorkIconP.x + 60,WorkIconP.y + 160 });
	//Font::Get()->RenderText(c, { WorkIconP.x + 90,WorkIconP.y + 160 });


}

void WorkBenchUI::GUIRender()
{
}




