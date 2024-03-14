#include "Framework.h"

PalModeUi::PalModeUi()
{
	baseDonut = new Quad(donutSize);
	baseDonut->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutGlass50.png");
	baseDonut->Pos() = center;

	selectA = new ClickQuad(selectSize);
	selectA->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	selectA->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (0.0f / 6.0f)), 200.0f * sinf(XM_2PI * (0.0f / 6.0f)), 0.0f);

	selectP = new ClickQuad(selectSize);
	selectP->GetQuad()->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_WorkBench.png");
	selectP->GetQuad()->Pos() = center + Vector3(200.0f * cosf(XM_2PI * (1.0f / 6.0f)), 200.0f * sinf(XM_2PI * (1.0f / 6.0f)), 0.0f);

	selectMiddle = new Quad(selectSize);
	selectMiddle->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_buildObject_PalBoxV2.png");
	selectMiddle->Pos() = center + Vector3(0.0f * cosf(XM_2PI * (2.0f / 6.0f)), 0.0f * sinf(XM_2PI * (2.0f / 6.0f)), 0.0f);

	donutPiece = new Quad(donutSize);
	donutPiece->GetMaterial()->SetDiffuseMap(L"Textures/UI/DonutPiece.png");
	donutPiece->Pos() = center;

}

PalModeUi::~PalModeUi()
{
	delete baseDonut;
	delete selectPalBox;
	delete selectWorkBench;
	delete selectMiddle;
	delete donutPiece;
}

void PalModeUi::Update()
{
}

void PalModeUi::Render()
{
}

void PalModeUi::PostRender()
{
}

void PalModeUi::GuiRender()
{
}

void PalModeUi::SetTexture()
{
}
