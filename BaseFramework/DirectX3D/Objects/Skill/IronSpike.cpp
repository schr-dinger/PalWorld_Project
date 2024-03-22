#include "Framework.h"
#include "IronSpike.h"

IronSpike::IronSpike()
{

	name = "������ũ";
	damage = 50;
	// startPos = Vector3();


	Spike = new Model("Spike");
	Spike->Rot().x += XM_PIDIV2;
	Spike->Scale() *= 5.0f;
	string a = "IR" + to_string(1);
	Spike->SetTag(a);
	Spike->GetMaterial(0)->SetDiffuseMap(L"Textures/Model/Spike/T_DustCristal_02.png");

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

		if (Spike->Pos().y < pal->GetTransform()->GlobalPos().y)  Spike->Pos().y += 3 * DELTA;
		else time += 3 * DELTA;

	}
	else
	{
		if (Spike->Pos().y < pal->GetTransform()->GlobalPos().y)  Spike->Pos().y += 3 * DELTA;
		else time += 3 * DELTA;

	}

	//particle->Update();
	Spike->UpdateWorld();
	col->UpdateWorld();

	// �浹ü �߰� �ʿ�




}

void IronSpike::Render()
{
	if (!Spike->Active()) return;



	Spike->Render();
	col->Render();
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
	if (enemy != nullptr)
	{
		Spike->UpdateWorld();
		enemy->UpdateWorld();


		Spike->Pos() = enemy->GlobalPos() + Vector3(0, -5, 0);
		Spike->UpdateWorld();
		//particle->Play(enemy->GlobalPos() + Vector3(0, 1, 0));

	}
	else
	{

		Spike->Pos() = pal->GetTransform()->GlobalPos() + Vector3(0, -5, 0) + pal->GetTransform()->Back() * 5;
		Spike->UpdateWorld();
		//particle->Play(pal->GetTransform()->GlobalPos() + pal->GetTransform()->Back() * 10);

	}



}

