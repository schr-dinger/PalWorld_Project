#include "Framework.h"
#include "IronSpike.h"

IronSpike::IronSpike()
{

	name = "스파이크";
	damage = 50;
	startPos = Vector3();

	FOR(3)
	{
		Spike[i] = new Model("Spike");
		Spike[i]->Rot().x += XM_PIDIV2;
		Spike[i]->Scale() *= 10.0f;

		particle[i] = new ParticleSystem("TextData/Particles/test2.fx");

	}


}

IronSpike::~IronSpike()
{
	FOR(3)
	{
		delete Spike[i];
		delete particle[i];
	}

}

void IronSpike::Update()
{
	if (!Spike[2]->Active()) return;

	
	FOR(3)
	{
		

		if (time > Life_Time)
		{
			Spike[i]->SetActive(false);
			SetSkill();
		}

		if (pal)
		{
			if (Start)
			{
				particle[i]->Play(pal->GetTransform()->GlobalPos() + Vector3(0, -10, (i + 1) * 5));
				danger += 3 * DELTA;

			}
			if (danger > 5)
			{
				if (Spike[i]->Pos().y < pal->GetTransform()->GlobalPos().y + 10)  Spike[i]->Pos().y += (i + 10) * DELTA;
				Start = false;
			}


			
			time += 1 * DELTA;

		}
		else
		{
			if (Spike[i]->Pos().y < 10)  Spike[i]->Pos().y += (i + 10) * DELTA;

			time += 1 * DELTA;


		}
		particle[i]->Update();
		Spike[i]->UpdateWorld();
	}


	// 충돌체 추가 필요
	



}

void IronSpike::Render()
{
	if (!Spike[2]->Active()) return;

	FOR(3)
	{
		particle[i]->Render();
		Spike[i]->Render();

	}

}

void IronSpike::GUIRender()
{
}

void IronSpike::Setpal(Pal* pal)
{
	this->pal = pal;
}

Collider* IronSpike::GetCol()
{
	return col;
}

bool IronSpike::Active()
{
	return Spike[0]->Active();
}

void IronSpike::SetActive(bool active)
{
	FOR(3)
	{
		Spike[i]->SetActive(active);
	}


}

void IronSpike::SetSkill()
{
	if (pal)
	{
		Start = true;
		danger = 0;
		FOR(3)
		{
			Spike[i]->Pos() = pal->GetTransform()->GlobalPos() + Vector3(0, -10, (i + 1) * 5);
		}
				
		// startPos = pal->GetTransform()->GlobalPos();
		dir = pal->GetTransform()->Back();

	}
	else
	{
		FOR(3)
		{
			Spike[i]->Pos() = Vector3(0, 0, 0);
		}
		// startPos = Vector3(0, 0, 0);
		dir = Vector3(0, 0, -1);

	}



}

