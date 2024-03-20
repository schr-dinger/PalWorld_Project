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

}

Pal::~Pal()
{
	delete shadowSphere;
	delete skill[0];
	delete skill[1];
	delete skill[2];
	
}
