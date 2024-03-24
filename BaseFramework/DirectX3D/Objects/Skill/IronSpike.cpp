#include "Framework.h"
#include "IronSpike.h"

IronSpike::IronSpike()
{

	name = "스파이크";
	damage = 120;
	// startPos = Vector3();


	Spike = new Model("Spike");
	Spike->Rot().x += XM_PIDIV2;
	Spike->Scale() *= 5.0f;
	Spike->SetTag("IR");
	Spike->GetMaterial(0)->SetDiffuseMap(L"Textures/Model/Spike/T_DustCristal_02.png");
	Spike->GetMaterial(0)->SetNormalMap(L"Textures/Model/Spike/T_Ice02_normal.png");
	Spike->SetActive(false);
	//particle = new ParticleSystem("TextData/Particles/Star.fx");

	col = new CapsuleCollider();
	col->SetParent(Spike);
	col->Rot().x += XM_PIDIV2;
	col->Scale() *= 0.4f;

}

IronSpike::~IronSpike()
{
	delete Spike;
	delete particle;
}

void IronSpike::Update()
{
	if (!Spike->Active()) return;



	if (time > Life_Time)
	{
		Spike->SetActive(false);
		SetSkill();
		time = 0;
	}


	if (pal)
	{

		if (Spike->Pos().y < pal->GetTransform()->GlobalPos().y)  Spike->Pos().y += 5 * DELTA;
		else time += 3 * DELTA;

	}
	else
	{
		if (Spike->Pos().y < pal->GetTransform()->GlobalPos().y)  Spike->Pos().y += 5 * DELTA;
		else time += 3 * DELTA;

	}

	//particle->Update();
	Spike->UpdateWorld();
	if (col->Active()) col->UpdateWorld();

	// 충돌체 추가 필요
	



}

void IronSpike::Render()
{
	if (!Spike->Active()) return;



	Spike->Render();
	if(col->Active()) col->Render();
	//particle->Render();


}

void IronSpike::GUIRender()
{


	Spike->GUIRender();


}



bool IronSpike::Active()
{
	return Spike->Active();
}

void IronSpike::SetActive(bool active)
{
	Spike->SetActive(active);
}

void IronSpike::SetSkill()
{
	if (!GetCol()->Active()) GetCol()->SetActive(true);


	if (enemy != nullptr)
	{
		Spike->UpdateWorld();
		enemy->UpdateWorld();


		Spike->Pos() = enemy->GlobalPos() + Vector3(0, -5, 0);
		Spike->UpdateWorld();
		//particle->Play(enemy->GlobalPos() + Vector3(0, 1, 0));
		time = 0.0f;

	}
	else
	{

		Spike->Pos() = pal->GetTransform()->GlobalPos() + Vector3(0, -5, 0) + pal->GetTransform()->Back() * 5;
		Spike->UpdateWorld();
		//particle->Play(pal->GetTransform()->GlobalPos() + pal->GetTransform()->Back() * 10);

	}



}

void IronSpike::SkillSound(Float3 pos)
{
	SOUND->Stop("EarthQuaSet");
	SOUND->Play("EarthQuaSet", pos);
}

void IronSpike::SkillHitSound(Float3 pos)
{
	SOUND->Stop("EarthQuakeHit");
	SOUND->Play("EarthQuakeHit", pos);
}

