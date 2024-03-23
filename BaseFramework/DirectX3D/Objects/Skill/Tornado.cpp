#include "Framework.h"

Tornado::Tornado()
{

	name = "토네이도";
	damage = 200;
	startPos = Vector3();
	
	Tornado1 = new Model("TestTornadoIn");
	Tornado2 = new Model("TestTornadoOut");
	Tornado3 = new Model("TestTornadoOut");
	Tornado4 = new Model("TestTornadoOut");
	Tornado5 = new Model("TestTornadoOut");
	//Tornado1->SetShader(L"Basic/Texture.hlsl");
	//Tornado2->SetShader(L"Basic/Texture.hlsl");
	//Tornado3->SetShader(L"Basic/Texture.hlsl");
	//Tornado4->SetShader(L"Basic/Texture.hlsl");
	//Tornado5->SetShader(L"Basic/Texture.hlsl");
	Tornado1->SetTag("P1");
	Tornado2->SetTag("P2");
	Tornado3->SetTag("P3");
	Tornado4->SetTag("P4");
	Tornado5->SetTag("P5");
	// 메티리얼 불러오기
	Tornado1->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/TestTornadoOut/T_Default_Noise04-2.png"));
	Tornado2->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/TestTornadoOut/T_Wind01-2.png"));
	Tornado3->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/TestTornadoOut/T_Wind03-2.png"));
	Tornado4->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/TestTornadoOut/T_Wind04-2.png"));
	Tornado5->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/TestTornadoOut/T_Wind05-2.png"));
	//셰이더 세팅하기
	//Tornado1->SetShader(L"Basic/Texture.hlsl");
	//Tornado2->SetShader(L"Basic/Texture.hlsl");
	//Tornado3->SetShader(L"Basic/Texture.hlsl");
	//Tornado4->SetShader(L"Basic/Texture.hlsl");
	//Tornado5->SetShader(L"Basic/Texture.hlsl");
	//셰이더 세팅하기2
	Tornado1->SetShader(L"Light/Light.hlsl");
	Tornado2->SetShader(L"Light/Light.hlsl");
	Tornado3->SetShader(L"Light/Light.hlsl");
	Tornado4->SetShader(L"Light/Light.hlsl");
	Tornado5->SetShader(L"Light/Light.hlsl");
	Tornado1->Rot().x = XM_PIDIV2;			
	Tornado2->Rot().x = XM_PIDIV2;
	//Tornado3->Rot().x = XM_PIDIV2;
	//Tornado4->Rot().x = XM_PIDIV2;
	//Tornado5->Rot().x = XM_PIDIV2;

	Tornado1->Scale() *= 0.03f;
	Tornado1->Scale().x *= 0.7f;
	Tornado1->Scale().y *= 0.6f;
	Tornado1->Scale().z *= 0.9f;
	Tornado2->Scale() *= 0.03f;;

	Tornado3->SetParent(Tornado2);
	Tornado4->SetParent(Tornado2);
	Tornado5->SetParent(Tornado2);

	SetActive(false); // 일단 모든 모델 비활성화

	Tornado1->UpdateWorld();
	Tornado2->UpdateWorld();
	Tornado3->UpdateWorld();
	Tornado4->UpdateWorld();
	Tornado5->UpdateWorld();

	col = new CapsuleCollider();
	col->SetParent(Tornado2);
	col->Scale() = Vector3(40, 25, 40);
	col->Rot().x = XM_PIDIV2;
	col->Pos().z = -45.0f;
	
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

	FOR(2) delete blendState[i];
	FOR(2) delete rasterizerState[i];
}

void Tornado::Update()
{
	if (!Tornado1->Active()) return;

	Tornado1->Rot().y += DELTA * 8;
	Tornado2->Rot().y += DELTA * 8;
	
	if (Tornado1->Rot().y > (2 * XM_PI))
	{
		Tornado1->Rot().y -= 2 * XM_PI;
		Tornado2->Rot().y -= 2 * XM_PI;
	}
	if (pal)
	{
		Tornado1->Pos() += dir * speed * DELTA;
		Tornado2->Pos() += dir * speed * DELTA;
		if (Distance(Tornado1->Pos(), startPos) >= dis)
		{
			SetActive(false);
			SetSkill();
		}
	}
	else
	{
		Tornado1->Pos() += dir * speed * DELTA;
		Tornado2->Pos() += dir * speed * DELTA;
		if (Distance(Tornado1->Pos(), startPos) >= dis)
		{
			SetActive(false);
			SetSkill();
		}
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
	if (!Tornado1->Active()) return;

	blendState[1]->SetState();
	rasterizerState[1]->SetState();
	Tornado1->Render();
	Tornado2->Render();
	Tornado3->Render();
	Tornado4->Render();
	Tornado5->Render();
	blendState[0]->SetState();
	rasterizerState[0]->SetState();
	col->Render();
}

void Tornado::GUIRender()
{
	//col->GUIRender();
	Tornado1->GUIRender();
	Tornado2->GUIRender();
	Tornado3->GUIRender();
	Tornado4->GUIRender();
	Tornado5->GUIRender();
}

//void Tornado::Setpal(Pal* pal)
//{
//	this->pal = pal;
//}
//
//Collider* Tornado::GetCol()
//{
//	return col;
//}

bool Tornado::Active()
{
	return Tornado1->Active();
}

void Tornado::SetActive(bool active)
{
	Tornado1->SetActive(active);
	Tornado2->SetActive(active);
	Tornado3->SetActive(active);
	Tornado4->SetActive(active);
	Tornado5->SetActive(active);
}

void Tornado::SetSkill()
{
	if (pal)
	{
		Tornado1->Pos() = pal->GetTransform()->GlobalPos();
		Tornado2->Pos() = pal->GetTransform()->GlobalPos();
		startPos = pal->GetTransform()->GlobalPos();
		if (enemy != nullptr)
		{
			dir = (enemy->GlobalPos() - pal->GetTransform()->GlobalPos()).GetNormalized();
			dir.y = 0;
		}
		else
		{
			dir = pal->GetTransform()->Back();
		}
		
	}
	else
	{
		Tornado1->Pos() = Vector3(0, 0, 0);
		Tornado2->Pos() = Vector3(0, 0, 0);
		startPos = Vector3(0, 0, 0);
		dir = Vector3(0, 0, -1);

	}
}

void Tornado::SkillSound(Float3 pos)
{
	SOUND->Stop("Sphere_Flash");
	SOUND->Play("Sphere_Flash", pos);
}

void Tornado::SkillHitSound(Float3 pos)
{
	//SOUND->Stop("WindCutterHit");
	if (!SOUND->IsPlaySound("WindCutterHit"))
	{
		SOUND->Play("WindCutterHit", pos);
	}
}
