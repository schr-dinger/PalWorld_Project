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

	// ÆÓ ¸ðµ¨µé
	ModelAnimator* tmp = new ModelAnimator("PenGuin");
	tmp->ReadClip("Idle");
	tmp->Pos() = { 770.0f,150.0f, -150.0f };
	tmp->Rot() = { 0,25 * (XM_2PI / 360.0f),0 };
	tmp->Scale() *= 3.0f;
	//tmp->Scale() *= 0.01f;
	tmp->SetActive(false);
	tmp->SetShader(L"Basic/Texture.hlsl");
	models.insert({ "ÆëÅ°", tmp });
	tmp = new ModelAnimator("Mammoth");
	tmp->ReadClip("Idle");
	tmp->Pos() = { 770.0f,150.0f, -150.0f };
	tmp->Rot() = { 0,25 * (XM_2PI / 360.0f),0 };
	tmp->Scale() *= 3.0f;
	tmp->SetActive(false);
	models.insert({ "±×¸°¸ð½º", tmp });
	tmp = new ModelAnimator("DarkWolf");
	tmp->ReadClip("Idle");
	tmp->Pos() = { 770.0f,150.0f, -150.0f };
	tmp->Rot() = { 0,25 * (XM_2PI / 360.0f),0 };
	tmp->Scale() *= 3.0f;
	tmp->SetActive(false);
	models.insert({ "´ÙÅ©¿ïÇÁ", tmp });
	//models.insert({ "ÆëÅ°", new ModelAnimator("PenGuin") });
	name = "";

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
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  // ´Ù °¡¸®±â
	//depthState[1]->DepthFunc(D3D11_COMPARISON_ALWAYS);

	FOR(5) isPlayed[i] = false;
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
		if (partyIcon[i]->MouseCollision() && UiManager::Get()->partyUiOn)
		{
			if (!isPlayed[i])
			{
				SOUND->Stop("UI_2");
				SOUND->Play("UI_2");
				isPlayed[i] = true;
			}
			if (KEY_DOWN(VK_LBUTTON) && partyIcon[i]->GetPal() != nullptr)
			{
				name = partyIcon[i]->GetPal()->name;
				models[name]->SetActive(true);
				models[name]->PlayClip(0);
				SOUND->Stop("UI_1");
				SOUND->Play("UI_1");
			}
		}
		else
		{
			isPlayed[i] = false;
		}
		
		partyIcon[i]->Update();
	}

	if (name != "")
	{
		//Vector3 tmp = CAM->Forward();
		//tmp.y = 0;
		if (KEY_DOWN('N'))
		{
			models[name]->Pos() = CAM->GlobalPos() + CAM->Forward() * 3;
		}
		models[name]->Update();

	}
}

void PartyUi::Render()
{
	//if (name != "")
	//{
	//	blendState[1]->SetState();
	//	depthState[1]->SetState();
	//	models[name]->Render();
	//	blendState[0]->SetState();
	//	depthState[0]->SetState();
	//}
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

	if (name != "")
	{
		blendState[1]->SetState();
		depthState[1]->SetState();
		models[name]->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();
	}

}

void PartyUi::GuiRender()
{
	
	if (name != "")
	{
		models[name]->GUIRender();
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
	
	if (name != "")
	{
		models[name]->SetActive(false);
	}
}
