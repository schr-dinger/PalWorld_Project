#include "Framework.h"

PartyUi::PartyUi()
{
	boxBase = new Quad(baseBoxSize);
	boxBase->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass80.png");
	boxBase->Pos() = { 640,360,0 };

	boxBaseName = new Quad(boxBaseNameSize);
	boxBaseName->GetMaterial()->SetDiffuseMap(L"Textures/Color/GrayGlass80.png");
	boxBaseName->Pos() = { 310,580,0 };


	boxBase->Update();
	boxBaseName->Update();

	FOR(5)
	{
		partyIcon[i] = new PartyBox();
		partyIcon[i]->GetQuad()->Pos() = partyIconP + Vector3(0, -i * 75.0f, 0);
	}

	model = nullptr;

	SetPal();

	FOR(2)
	{
		blendState[i] = new BlendState;
		depthState[i] = new DepthStencilState;
	}
	blendState[1]->AlphaToCoverage(true);
	//blendState[1]->Alpha(false);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  // 다 가리기

}

PartyUi::~PartyUi()
{
	delete boxBase;
	delete boxBaseName;

	FOR(5)
	{
		delete partyIcon[i];
	}

}

void PartyUi::Update()
{
	FOR(5)
	{
		if (partyIcon[i]->MouseCollision() && KEY_DOWN(VK_LBUTTON) && UiManager::Get()->partyUiOn && partyIcon[i]->GetPal() != nullptr)
		{
			if (model != nullptr)
			{
				delete model;
			}
			model = new ModelAnimator(partyIcon[i]->GetPal()->GetModelName());
			model->ReadClip("Idle");
			//model->ReadClip("Run");
			model->PlayClip(0);
			model->Pos() = { 770.0f,150.0f, -150.0f };
			model->Rot() = { 0,25 * (XM_2PI / 360.0f),0 };
			model->Scale() *= 3.0f;
			model->SetActive(true);

		}


		partyIcon[i]->Update();
	}

	if (model != nullptr)
	{
		model->Update();
	}

	//UiMouseManager::Get()->Update();

}

void PartyUi::Render()
{
}

void PartyUi::PostRender()
{
	boxBase->Render();
	boxBaseName->Render();



	FOR(5)
	{
		partyIcon[i]->PostRender();
	}

	{
		Font::Get()->SetStyle("PartyBoxName");
		Font::Get()->RenderText("Party", { 170.0f, 590.0f });

		Font::Get()->SetStyle("Default");
		Font::Get()->GetDC()->EndDraw();
		Font::Get()->GetDC()->BeginDraw();
	}

	if (model != nullptr)
	{
		blendState[1]->SetState();
		depthState[1]->SetState();
		model->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();
	}

}

void PartyUi::GuiRender()
{
	if (model != nullptr)
	{
		model->GUIRender();
	}
}

void PartyUi::SetPal()
{
	FOR(5)
	{
		partyIcon[i]->SetPal(PlayerPalsManager::Get()->GetPalvector()[(i)]);
		partyIcon[i]->SetTexture3();
	}

}

void PartyUi::ClearModel()
{
	//
	if (model != nullptr)
	{
		//오류남
		//delete model;
		model->SetActive(false);
	}

}
