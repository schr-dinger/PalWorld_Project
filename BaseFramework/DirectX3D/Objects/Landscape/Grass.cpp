#include "Framework.h"

Grass::Grass(Transform* transform) : transform(transform)
{

	impostor = new Quad(Vector2(1920.0f, 1080.0f)*0.005f);
	impostor->GetMaterial()->SetDiffuseMap(L"Textures/Model/Grass1/GrassImpostor_1.png");

	FOR(2)
	{
		blendState[i] = new BlendState();
	}

	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);

}

Grass::~Grass()
{
	delete impostor;
	FOR(2)
	{
		delete blendState[i];
	}

}

void Grass::Update()
{
	transform->UpdateWorld();

	impostor->Pos() = transform->Pos() + Vector3(0.0f, 0.5f, 0.0f);
	impostor->Rot().y = CAM->GetParent()->Rot().y + XM_PI;
	impostor->Update();
}

void Grass::Render()
{
	if (transform->Active()) return;

	if (transform->Pos().y < 0) return;
	blendState[1]->SetState();
	impostor->Render();
	blendState[0]->SetState();
}

void Grass::GUIRender()
{
}
