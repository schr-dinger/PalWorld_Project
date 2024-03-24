#include "Framework.h"
#include "PalBoxUi.h"

PalBoxUi::PalBoxUi()
{
	//boxBase = new Quad(L"Textures/UI/T_gauge_HP_base.png");
	boxBase = new Quad(baseBoxSize);
	boxBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	boxBase->Pos() = { 640,400,0 };

	boxBaseName = new Quad(boxBaseNameSize);
	boxBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	boxBaseName->Pos() = { 640,560,0 };


	partyBase = new Quad(partyBaseSize);
	partyBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	partyBase->Pos() = { 235.0f,367.5f,0.0f };
	partyBase->SetTag("partyBase");

	partyBaseName = new Quad(partyBaseNameSize);
	partyBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	partyBaseName->Pos() = { 235,560,0 };

	boxBase->Update();
	boxBaseName->Update();

	partyBase->Update();
	partyBaseName->Update();

	FOR(30)
	{
		boxIcon[i] = new PalClickQuad();
		boxIcon[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0)*60.0f;
		boxIconBase[i] = new PalClickQuad();
		boxIconBase[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0) * 60.0f;
		boxIconSound[i] = false;
	}

	FOR(5)
	{
		partyIcon[i] = new PartyBox();
		partyIcon[i]->GetQuad()->Pos() = partyIconP + Vector3(0, -i * 75.0f, 0);
		partyIconSound[i] = false;
	}

	SetPal();
}

PalBoxUi::~PalBoxUi()
{
	delete boxBase;
	delete boxBaseName;
	delete partyBase;
	delete partyBaseName;

	FOR(30)
	{
		delete boxIcon[i];
		delete boxIconBase[i];
	}

	FOR(5)
	{
		delete partyIcon[i];
	}

}

void PalBoxUi::Update()
{
	FOR(30)
	{
		boxIcon[i]->SetTexture();
		if (boxIcon[i]->MouseCollision())
		{
			boxIconBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
			if (!boxIconSound[i])
			{
				SOUND->Stop("UI_2");
				SOUND->Play("UI_2", 0.7f);
				boxIconSound[i] = true;
			}
			if (KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() != nullptr)
			{
				int tmp = UiMouseManager::Get()->GetIndex();
				Pal* palTmp = PlayerPalsManager::Get()->GetPalvector()[i + 5];
				PlayerPalsManager::Get()->GetPalvector()[i + 5] = PlayerPalsManager::Get()->GetPalvector()[tmp];
				PlayerPalsManager::Get()->GetPalvector()[tmp] = palTmp;
				SetPal();

				UiMouseManager::Get()->SetPal(nullptr);
				SOUND->Stop("UI_1");
				SOUND->Play("UI_1");
			}
			else if (KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() == nullptr)
			{
				UiMouseManager::Get()->SetPal(boxIcon[i]->GetPal());
				UiMouseManager::Get()->SetIndex(i + 5);
				SOUND->Stop("UI_1");
				SOUND->Play("UI_1");
			}
		}
		else
		{
			boxIconBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
			boxIconSound[i] = false;
		}

		boxIcon[i]->Update();
		boxIconBase[i]->Update();
	}

	FOR(5)
	{
		if (partyIcon[i]->MouseCollision())
		{
			if (!partyIconSound[i])
			{
				SOUND->Stop("UI_2");
				SOUND->Play("UI_2", 0.7f);
				partyIconSound[i] = true;
			}
			if (KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() != nullptr)
			{
				int tmp = UiMouseManager::Get()->GetIndex();
				Pal* palTmp = PlayerPalsManager::Get()->GetPalvector()[i];
				PlayerPalsManager::Get()->GetPalvector()[i] = PlayerPalsManager::Get()->GetPalvector()[tmp];
				PlayerPalsManager::Get()->GetPalvector()[tmp] = palTmp;
				SetPal();

				UiMouseManager::Get()->SetPal(nullptr);
				SOUND->Stop("UI_1");
				SOUND->Play("UI_1");
			}
			else if (KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() == nullptr)
			{
				UiMouseManager::Get()->SetPal(partyIcon[i]->GetPal());
				UiMouseManager::Get()->SetIndex(i);
				SOUND->Stop("UI_1");
				SOUND->Play("UI_1");
			}


		}
		else
		{
			partyIconSound[i] = false;
		}

		
		partyIcon[i]->Update();
	}
	UiMouseManager::Get()->Update();

}

void PalBoxUi::Render()
{
}

void PalBoxUi::PostRender()
{
	boxBase->Render();
	boxBaseName->Render();

	partyBase->Render();
	partyBaseName->Render();

	FOR(30)
	{
		boxIconBase[i]->Render();
		boxIcon[i]->Render();
	}

	FOR(5)
	{
		partyIcon[i]->PostRender();
	}

	{
		Font::Get()->SetStyle("PartyBoxName");
		Font::Get()->RenderText("Party", { 96.0f, 572.0f });

		Font::Get()->SetStyle("PartyBoxName");
		Font::Get()->RenderText("Box", { 402.0f, 572.0f });

		Font::Get()->SetStyle("Default");
		Font::Get()->GetDC()->EndDraw();
		Font::Get()->GetDC()->BeginDraw();
	}

	//UiMouseManager::Get()->Render();

}

void PalBoxUi::GuiRender()
{
	partyBase->GUIRender();
}

void PalBoxUi::SetPal()
{

	FOR(5)
	{
		partyIcon[i]->SetPal(PlayerPalsManager::Get()->GetPalvector()[(i)]);
		partyIcon[i]->SetTexture3();

	}

	FOR(30)
	{
		boxIcon[i]->SetPal(PlayerPalsManager::Get()->GetPalvector()[(i+5)]);
	}
}
