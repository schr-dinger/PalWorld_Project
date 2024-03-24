#include "Framework.h"

BuildUi::BuildUi()
{
	baseDonut = new Quad(donutSize);
	baseDonut->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutGlass50.png");
	baseDonut->Pos() = center;

	selectPalBox = new ClickQuad(selectSize);
	selectPalBox->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	selectPalBox->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI*(0.0f/6.0f)), 200.0f * sinf(XM_2PI * (0.0f / 6.0f)),0.0f);

	selectWorkBench = new ClickQuad(selectSize);
	selectWorkBench->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_WorkBench.png");
	selectWorkBench->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (1.0f / 6.0f)), 200.0f * sinf(XM_2PI * (1.0f / 6.0f)), 0.0f);

	selectMiddle = new Quad(selectSize);
	selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	selectMiddle->Pos() = center + Vector3(0.0f * cosf(XM_2PI * (2.0f / 6.0f)), 0.0f * sinf(XM_2PI * (2.0f / 6.0f)), 0.0f);

	donutPiece = new Quad(donutSize);
	donutPiece->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutPiece.png");
	donutPiece->Pos() = center;

}

BuildUi::~BuildUi()
{
	delete baseDonut;
	delete selectPalBox;
	delete selectWorkBench;
	delete selectMiddle;
	delete donutPiece;
}

void BuildUi::Update()
{
	SetTexture();
	donutPiece->Rot().z = pieceRot;

	

	if (selectPalBox->MouseCollision())
	{
		if (!isPalBox)
		{
			isPalBox = true;
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2");
		}
		pieceRot = XM_2PI * (0.0f / 6.0f);
		donutPiece->SetActive(true);
		if (KEY_DOWN(VK_LBUTTON) && UiManager::Get()->buildUiOn)
		{
			UiManager::Get()->buildPalBox = true;
			UiManager::Get()->buildUiOn = false;
			mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
			SOUND->Stop("UI_1");
			SOUND->Play("UI_1");
		}
	}
	else if (!selectPalBox->MouseCollision())
	{
		donutPiece->SetActive(false);
		isPalBox = false;
	}

	if (selectWorkBench->MouseCollision())
	{
		if (!isWorkBench)
		{
			isWorkBench = true;
			SOUND->Stop("UI_2");
			SOUND->Play("UI_2");
		}
		pieceRot = XM_2PI * (1.0f / 6.0f);
		donutPiece->SetActive(true);
		if (KEY_DOWN(VK_LBUTTON) && UiManager::Get()->buildUiOn)
		{
			UiManager::Get()->buildWorkBench = true;
			UiManager::Get()->buildUiOn = false;
			mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
			SOUND->Stop("UI_1");
			SOUND->Play("UI_1");
		}
	}
	else if (!selectWorkBench->MouseCollision())
	{
		if (!isPalBox) // 위에서 선택 안됐을 때만 false
		{
			donutPiece->SetActive(false);
		}
		isWorkBench = false;
	}
	

	baseDonut->Update();
	selectPalBox->Update();
	selectWorkBench->Update();
	selectMiddle->Update();
	donutPiece->Update();
}

void BuildUi::Render()
{
}

void BuildUi::PostRender()
{
	baseDonut->Render();
	donutPiece->Render();
	selectPalBox->Render();
	selectWorkBench->Render();
	selectMiddle->Render();
}

void BuildUi::GuiRender()
{
}

void BuildUi::SetTexture()
{
	if (selectPalBox->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	}
	else if(selectWorkBench->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_WorkBench.png");
	}
	else
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	}
}
