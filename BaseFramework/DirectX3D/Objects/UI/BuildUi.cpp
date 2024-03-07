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

}

BuildUi::~BuildUi()
{
	delete baseDonut;
	delete selectPalBox;
	delete selectWorkBench;
	delete selectMiddle;
}

void BuildUi::Update()
{
	SetTexture();

	if (selectPalBox->MouseCollision() && KEY_DOWN(VK_LBUTTON))
	{
		UiManager::Get()->buildPalBox = true;
		UiManager::Get()->buildUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}

	if (selectWorkBench->MouseCollision() && KEY_DOWN(VK_LBUTTON))
	{
		UiManager::Get()->buildWorkBench = true;
		UiManager::Get()->buildUiOn = false;
		mousePos = { WIN_WIDTH / 2.0f,WIN_HEIGHT / 2.0f };
	}


	baseDonut->Update();
	selectPalBox->Update();
	selectWorkBench->Update();
	selectMiddle->Update();
}

void BuildUi::Render()
{
}

void BuildUi::PostRender()
{
	baseDonut->Render();
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
