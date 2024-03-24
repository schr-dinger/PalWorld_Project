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

	SetBase = new Quad(Vector2(200, 150));
	SetBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	SetBase->Pos() = { SetIconP.x, SetIconP.y ,0 };

	SetButton1 = new ClickQuad(Vector2(50, 50));
	SetButton1->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	SetButton1->GetQuad()->Pos() = { SetIconP.x - 50, SetIconP.y - 20 ,0 };

	SetButton2 = new ClickQuad(Vector2(50, 50));
	SetButton2->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	SetButton2->GetQuad()->Pos() = { SetIconP.x + 50, SetIconP.y - 20 ,0 };


	FOR(5)
	{
		test[i] = new WorkSlot(i);
		test[i]->GetQuad()->Pos() = Vector3(WorkIconP.x + i * 60 - 120, WorkIconP.y + 100, 0);
		test[i]->GetBase()->GetQuad()->Pos() = Vector3(WorkIconP.x + i * 60 - 120, WorkIconP.y + 100, 0);

	}

	WorkBase->Update();
	WorkBaseName->Update();
	SetBase->Update();
	SetButton1->Update();
	SetButton2->Update();

}

WorkBenchUI::~WorkBenchUI()
{
	delete WorkBase;
	delete WorkBaseName;
	delete SetBase;
	delete SetButton1;
	delete SetButton2;
	FOR(5)
	{
		delete test[i];
	}


}

void WorkBenchUI::Update()
{



	if (SetButton1->MouseCollision() && KEY_UP(VK_LBUTTON))
	{
		Count++;
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}
	else if (SetButton2->MouseCollision() && KEY_UP(VK_LBUTTON))
	{
		if (Count != 1) Count--;
		SOUND->Stop("UI_3");
		SOUND->Play("UI_3");
	}

	FOR(5)
	{
		test[i]->SetCount(Count);

		if (test[i]->CheckItem() && StructureManager::Get()->GetWorkBench()->GetItem() == nullptr && test[i]->MouseCollision() && KEY_DOWN('J'))
		{
			SOUND->Play("UI_3");
			test[i]->MakeItem(Count);
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
	SetBase->Render();
	SetButton1->Render();
	SetButton2->Render();

	FOR(5)
	{
		test[i]->Render();

	}

	Font::Get()->SetStyle("FieldEquibName");
	Font::Get()->RenderText(" �۾��� ", { WorkIconP.x - 40,WorkIconP.y + 160 });
	string a = to_string(Count);

	Font::Get()->RenderText("Count : ", {SetIconP.x - 50 ,SetIconP.y + 50});
	Font::Get()->RenderText(a, { SetIconP.x + 20 ,SetIconP.y + 50 });



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




