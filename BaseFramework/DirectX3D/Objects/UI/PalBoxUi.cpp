#include "Framework.h"
#include "PalBoxUi.h"

PalBoxUi::PalBoxUi()
{
	//boxBase = new Quad(L"Textures/UI/T_gauge_HP_base.png");
	boxBase = new Quad(baseSize);
	boxBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	boxBase->Pos() = { 640,400,0 };


	FOR(30)
	{
		boxIcon[i] = new PalClickQuad();
		boxIcon[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0)*60.0f;
		boxIconBase[i] = new PalClickQuad();
		boxIconBase[i]->GetQuad()->Pos() = boxIconP + Vector3(i % 6, -i / 6, 0) * 60.0f;
	}

	//boxIcon[0]->SetPal(PlayerPalsManager::Get()->GetPal(0));

	SetPal();
}

PalBoxUi::~PalBoxUi()
{
	delete boxBase;
	FOR(30)
	{
		delete boxIcon[i];
		delete boxIconBase[i];
	}
}

void PalBoxUi::Update()
{

	FOR(30)
	{
		boxIcon[i]->SetTexture();

		if (boxIcon[i]->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() == nullptr )
		{
			UiMouseManager::Get()->SetPal(boxIcon[i]->GetPal());
			UiMouseManager::Get()->SetIndex(i);
		}

		if (boxIcon[i]->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiMouseManager::Get()->GetPal() != nullptr)
		{
			int tmp = UiMouseManager::Get()->GetIndex();
			Pal* palTmp = PlayerPalsManager::Get()->GetPalvector()[i];
			PlayerPalsManager::Get()->GetPalvector()[i] = PlayerPalsManager::Get()->GetPalvector()[tmp];
			PlayerPalsManager::Get()->GetPalvector()[tmp] = palTmp;
			SetPal();

			UiMouseManager::Get()->SetPal(nullptr);

		}



		if (boxIconBase[i]->MouseCollision())
		{
			boxIconBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Cyan.png");
		}
		else
		{
			boxIconBase[i]->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		}



		boxIcon[i]->Update();
		boxIconBase[i]->Update();

	}

	UiMouseManager::Get()->Update();

	boxBase->Update();
}

void PalBoxUi::Render()
{
}

void PalBoxUi::PostRender()
{
	boxBase->Render();
	FOR(30)
	{
		boxIconBase[i]->Render();
		boxIcon[i]->Render();
	}
	UiMouseManager::Get()->Render();

}

void PalBoxUi::GuiRender()
{
}

void PalBoxUi::SetPal()
{
	FOR(30)
	{
		boxIcon[i]->SetPal(PlayerPalsManager::Get()->GetPalvector()[(i)]);
	}
}
