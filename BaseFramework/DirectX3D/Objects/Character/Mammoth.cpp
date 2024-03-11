#include "Framework.h"

Mammoth::Mammoth(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:transform(transform), instancing(instancing), index(index)
{
}

Mammoth::~Mammoth()
{
}

void Mammoth::Update()
{
}

void Mammoth::Render()
{
}

void Mammoth::PostRender()
{
}

void Mammoth::GUIRender()
{
}

void Mammoth::SetTarget(Transform* target)
{
}

Transform* Mammoth::GetTransform()
{
	return nullptr;
}

CapsuleCollider* Mammoth::GetCollider()
{
	return nullptr;
}


float Mammoth::GetCurHp()
{
	return 0.0f;
}

void Mammoth::FieldAttack()
{
}

void Mammoth::Attack()
{
}

void Mammoth::Damage()
{
}

void Mammoth::Spawn(Vector3 pos)
{
}

void Mammoth::Summons(Vector3 pos)
{
}
