#include "Framework.h"

IceSpear::IceSpear()
{
	name = "얼음창";
	damage = 100;
	startPos = Vector3();

	iceSpear = new Model("IceSpear");
	iceSpear->SetTag("IS");
	iceSpear->GetMaterial(0)->SetDiffuseMap(Texture::Add(L"Textures/Model/IceSpear/iceTest1.png"));
	iceSpear->GetMaterial(0)->SetSpecularMap(L"Textures/Model/IceSpear/T_IceCool_D.png");
	iceSpear->GetMaterial(0)->SetNormalMap(L"Textures/Model/IceSpear/T_CritalSoft_N.png");
	iceSpear->Scale().x *= 0.002f;
	iceSpear->Scale().y *= 0.003f;
	iceSpear->Scale().z *= 0.002f;
	//iceSpear->Rot().y = XM_PIDIV2;
	//iceSpear->Rot().z = XM_PIDIV2;
	iceSpear->Rot().x = XM_PIDIV2;
	SetActive(false); // 일단 모든 모델 비활성화

	col = new CapsuleCollider();
	col->SetParent(iceSpear);
	col->Scale() = Vector3(85, 143, 85);
	col->Pos().y = 6.8f;

}

IceSpear::~IceSpear()
{
	delete iceSpear;
}

void IceSpear::Update()
{
	if (!iceSpear->Active()) return;

	if (pal)
	{
		iceSpear->Pos() += dir * speed * DELTA;
		if (Distance(iceSpear->Pos(), startPos) >= dis)
		{
			SetActive(false);
			SetSkill();
		}
	}
	else
	{
		iceSpear->Pos() += dir * speed * DELTA;
		if (Distance(iceSpear->Pos(), startPos) >= dis)
		{
			SetActive(false);
			SetSkill();
		}
	}

	iceSpear->UpdateWorld();
	col->UpdateWorld();
}

void IceSpear::Render()
{
	if (!iceSpear->Active()) return;

	iceSpear->Render();
	col->Render();
}

void IceSpear::GUIRender()
{
	iceSpear->GUIRender();
}

bool IceSpear::Active()
{

	return iceSpear->Active();
}

void IceSpear::SetActive(bool active)
{
	iceSpear->SetActive(active);
}

void IceSpear::SetSkill()
{
	iceSpear->Pos() = pal->GetTransform()->GlobalPos() + height;
	startPos = pal->GetTransform()->GlobalPos() + height;
	if (enemy != nullptr) // 적 타겟
	{
		iceSpear->UpdateWorld();
		enemy->UpdateWorld();
		dir = (enemy->GlobalPos() + Vector3(0,1.0f,0)) - iceSpear->GlobalPos();
		dir = dir.GetNormalized();
		Vector3 tmpRot;
		Vector3 c = dir;
		tmpRot.y = atan2(c.x, c.z);
		Vector2 a = { c.x, c.z };
		tmpRot.x = atan2(a.Length(), c.y) + XM_PI;
		iceSpear->Rot().x = tmpRot.x;
		iceSpear->Rot().y = tmpRot.y;

		iceSpear->UpdateWorld();

		iceSpear->UpdateWorld();
	}
	else // 적 타겟 없으면 대충 앞에다가
	{
		iceSpear->UpdateWorld();

		dir = (pal->GetTransform()->GlobalPos() + pal->GetTransform()->Back() * 10) - iceSpear->GlobalPos();
		dir = dir.GetNormalized();
		Vector3 tmpRot;
		Vector3 c = dir;
		tmpRot.y = atan2(c.x, c.z);
		Vector2 a = { c.x, c.z };
		tmpRot.x = atan2(a.Length(), c.y) + XM_PI;
		iceSpear->Rot().x = tmpRot.x;
		iceSpear->Rot().y = tmpRot.y;

		iceSpear->UpdateWorld();
	}
}

void IceSpear::SkillSound()
{
	SOUND->Stop("IceMissileShoot");
	SOUND->Play("IceMissileShoot");
}

void IceSpear::SkillHitSound()
{
	int tmp = RANDOM->Int(0, 1);
	switch (tmp)
	{
	case 0:
		SOUND->Stop("IceMissileHit_1");
		SOUND->Stop("IceMissileHit_2");
		SOUND->Play("IceMissileHit_1");
		break;
	case 1:
		SOUND->Stop("IceMissileHit_1");
		SOUND->Stop("IceMissileHit_2");
		SOUND->Play("IceMissileHit_2");
		break;
	default:
		break;
	}
	
	
}
