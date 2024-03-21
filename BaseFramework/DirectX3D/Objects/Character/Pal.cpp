#include "Framework.h"

Pal::Pal()
{
	name = "";
	modelName = "";
	skill[0] = nullptr;
	skill[1] = nullptr;
	skill[2] = nullptr;
	icon = nullptr;
	iconC = nullptr;
	isUIOn = false;
	onUITime = 0.0f;
	shadowSphere = nullptr;

	emote = new Quad(Vector2(0.5f, 0.5f));
	emote->GetMaterial()->SetDiffuseMap(L"Textures/UI/T_icon_pal_work_2_1.png");

	FOR(2)
		blendState[i] = new BlendState();
	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);

	damage = 0.0f;
	
	// UI
	palQuad = new Quad(Vector2(1, 1));
	palQuad->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50.png");
	palQuad->Scale() = { 110.0f, 30.0f, 0.0f };
	palQuad->SetTag("SQ1");
	palQuad->Pos() = { 138.0f, 95.0f, 0.0f };

	palHpBar = new ProgressBar(
		L"Textures/Color/Red.png",
		L"Textures/Color/BlackGlass.png"
	);
	palHpBar->SetTag("Shp");
	palHpBar->Scale().x = 0.4f;
	palHpBar->Scale().y = 0.015f;
	palHpBar->Pos() = { 138.0f, 85.5f, 0.0f };
}

Pal::~Pal()
{
	delete skill[0];
	delete skill[1];
	delete skill[2];
	
	delete palQuad;
	delete palHpBar;
}
