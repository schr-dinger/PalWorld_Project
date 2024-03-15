#include "Framework.h"

PalModeUi::PalModeUi()
{
	baseDonut = new Quad(donutSize);
	baseDonut->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutGlass50.png");
	baseDonut->Pos() = center;

	selectA = new ClickQuad(selectSize);
	selectA->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/devilIcon.png");
	selectA->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (0.0f / 6.0f)), 200.0f * sinf(XM_2PI * (0.0f / 6.0f)), 0.0f);

	selectP = new ClickQuad(selectSize);
	selectP->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/angelIcon.png");
	selectP->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (3.0f / 6.0f)), 200.0f * sinf(XM_2PI * (3.0f / 6.0f)), 0.0f);

	selectMiddle = new Quad(selectSize);
	selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	selectMiddle->Pos() = center + Vector3(0.0f * cosf(XM_2PI * (0.0f / 6.0f)), 0.0f * sinf(XM_2PI * (0.0f / 6.0f)), 0.0f);

	donutPiece = new Quad(donutSize);
	donutPiece->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutPiece.png");
	donutPiece->Pos() = center;

}

PalModeUi::~PalModeUi()
{
	delete baseDonut;
	delete selectMiddle;
	delete donutPiece;

	delete selectA;
	delete selectP;
}

void PalModeUi::Update()
{
	SetTexture();
	donutPiece->Rot().z = pieceRot;

	if (selectA->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiManager::Get()->palModeUiOn)
	{
		PlayerPalsManager::Get()->SetMode(PlayerPalsManager::MODE::AGGRESSIVE);
		UiManager::Get()->palModeUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}

	if (selectA->MouseCollision())
	{
		pieceRot = XM_2PI * (0.0f / 6.0f);
	}

	if (selectP->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiManager::Get()->palModeUiOn)
	{
		PlayerPalsManager::Get()->SetMode(PlayerPalsManager::MODE::PASSIVE);
		UiManager::Get()->palModeUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}

	if (selectP->MouseCollision())
	{
		pieceRot = XM_2PI * (3.0f / 6.0f);
	}


	baseDonut->Update();
	selectA->Update();
	selectP->Update();
	selectMiddle->Update();
	donutPiece->Update();

}

void PalModeUi::Render()
{
}

void PalModeUi::PostRender()
{
	baseDonut->Render();
	selectA->Render();
	selectP->Render();
	donutPiece->Render();
	selectMiddle->Render();

}

void PalModeUi::GuiRender()
{
}

void PalModeUi::SetTexture()
{
	if (selectA->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/devilIcon.png");
	}
	else if (selectP->MouseCollision())
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/angelIcon.png");
	}
	else
	{
		selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/Color/PureGlass.png");
	}

}
