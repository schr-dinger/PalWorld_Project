#include "Framework.h"

Tornado::Tornado()
{

	name = "토네이도";
	damage = 30;
	
	Tornado1 = new Model("TestTornadoIn");
	Tornado2 = new Model("TestTornadoOut");
	Tornado3 = new Model("TestTornadoOut");
	Tornado4 = new Model("TestTornadoOut");
	Tornado5 = new Model("TestTornadoOut");
	Tornado1->SetShader(L"Basic/Texture.hlsl");
	Tornado2->SetShader(L"Basic/Texture.hlsl");
	Tornado3->SetShader(L"Basic/Texture.hlsl");
	Tornado4->SetShader(L"Basic/Texture.hlsl");
	Tornado5->SetShader(L"Basic/Texture.hlsl");
	Tornado1->SetTag("P1");
	Tornado2->SetTag("P2");
	Tornado3->SetTag("P3");
	Tornado4->SetTag("P4");
	Tornado5->SetTag("P5");
	Tornado1->Rot().x = XM_PIDIV2;
	Tornado2->Rot().x = XM_PIDIV2;
	Tornado3->Rot().x = XM_PIDIV2;
	Tornado4->Rot().x = XM_PIDIV2;
	Tornado5->Rot().x = XM_PIDIV2;

	Tornado1->Scale() = { 0.7, 0.6, 0.9 };

	Tornado3->SetParent(Tornado2);
	Tornado4->SetParent(Tornado2);
	Tornado5->SetParent(Tornado2);

	SetActive(false); // 일단 모든 모델 비활성화

	col = new CapsuleCollider();
	col->SetParent(Tornado1);
	
	FOR(2) blendState[i] = new BlendState();

	blendState[1]->Alpha(true);
	blendState[1]->AlphaToCoverage(true);

	FOR(2) rasterizerState[i] = new RasterizerState();
	rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

Tornado::~Tornado()
{
	delete Tornado1;
	delete Tornado2;
	delete Tornado3;
	delete Tornado4;
	delete Tornado5;

	delete col;

	FOR(2) delete blendState[i];
	FOR(2) delete rasterizerState[i];
}

void Tornado::Update()
{
	if (!Tornado1->Active()) return;

	Tornado1->Rot().y += DELTA * 5;
	Tornado2->Rot().y += DELTA * 5;
	
	if (Tornado1->Rot().y > (2 * XM_PI))
	{
		Tornado1->Rot().y -= 2 * XM_PI;
		Tornado2->Rot().y -= 2 * XM_PI;
	}
	if (pal)
	{
		Tornado1->Pos() = pal->GetTransform()->GlobalPos();
		Tornado2->Pos() = pal->GetTransform()->GlobalPos();
		Tornado1->Pos() += pal->GetTransform()->Back() * speed * DELTA;
		Tornado2->Pos() += pal->GetTransform()->Back() * speed * DELTA;
	}
	else
	{
		Tornado1->Pos() += Vector3(0, 0, -1) * speed * DELTA;
		Tornado2->Pos() += Vector3(0, 0, -1) * speed * DELTA;
	}

	Tornado1->UpdateWorld();
	Tornado2->UpdateWorld();
	Tornado3->UpdateWorld();
	Tornado4->UpdateWorld();
	Tornado5->UpdateWorld();
	col->UpdateWorld();

}

void Tornado::Render()
{
	blendState[1]->SetState();
	rasterizerState[1]->SetState();
	Tornado1->Render();
	Tornado2->Render();
	Tornado3->Render();
	Tornado4->Render();
	Tornado5->Render();
	blendState[0]->SetState();
	rasterizerState[0]->SetState();
}

void Tornado::GUIRender()
{
}

void Tornado::Setpal(Pal* pal)
{
	this->pal = pal;
}

Collider* Tornado::GetCol()
{
	return col;
}

void Tornado::SetActive(bool active)
{
	Tornado1->SetActive(active);
	Tornado2->SetActive(active);
	Tornado3->SetActive(active);
	Tornado4->SetActive(active);
	Tornado5->SetActive(active);
}
