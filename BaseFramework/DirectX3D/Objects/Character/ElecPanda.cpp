#include "Framework.h"
#include "ElecPanda.h"

ElecPanda::ElecPanda() : ModelAnimator("ElecP")
{

	transform = new Transform();
	collider = new CapsuleCollider();

	ReadClip("ElecP_run");
	ReadClip("ElecP_skill");
	ReadClip("ElecP_damage");
	ReadClip("ElecP_idle");

	collider->SetParent(transform);
	collider->Scale() *= 0.5f;

	Scale() *= 0.01f;

	GetClip(ATTACK)->SetEvent(bind(&ElecPanda::EndAttack, this), 0.7f);
}

ElecPanda::~ElecPanda()
{
	delete transform;
	delete collider;

}

void ElecPanda::Update()
{
	AI();

	transform->SetWorld(GetTransformByNode(5));

	velocity = target->GlobalPos() - transform->GlobalPos(); // target 지정하고


	Pos() += velocity * DELTA;
	if (KEY_PRESS('W'))
	{
		Pos() -= Forward() * 10 * DELTA;
	}
	if (KEY_PRESS('S'))
	{
		Pos() += Forward() * 10 * DELTA;
	}

	if (KEY_PRESS(VK_SPACE))
	{
		collider->UpdateWorld();

		SetState(ATTACK);
		//Pos().z -= 100 * DELTA;
		
			
	}

	if (test)
	{
		test2 += 10 * DELTA;
		if (test2 > 0.5)
		{
			test = false;
		}
	}
	


	ModelAnimator::Update();

	collider->UpdateWorld();

}

void ElecPanda::Render()
{
	if (!test)
	{
		ModelAnimator::Render();
		collider->Render();
	}
	
	
}

void ElecPanda::GUIRender()
{
	Model::GUIRender();
}

void ElecPanda::SetTarget(Transform* target)
{
	this->target = target;

}

void ElecPanda::AI()
{

	void Attack();
	void Move();

}

void ElecPanda::Move()
{
	if (curState == ATTACK) return;
	if (curState == HIT) return;


	Pos() += velocity.GetNormalized() * 20 * DELTA;
	Rot().y = atan2(velocity.x, velocity.z) + XM_PI; 

}

void ElecPanda::Test(Collider* collider)
{

	if (this->collider->IsCollision(collider))
	{
		this->collider->SetColor(1, 1, 1);
	}
	else
	{
		this->collider->SetColor(1, 0, 0);
	}



}

/*
void ElecPanda::EnCounter()
{
	



}



void ElecPanda::Attack()
{



	SetState(ATTACK);


}

void ElecPanda::SetAnim()
{


}
*/

void ElecPanda::Hit()
{
	// hp 비율이나 크리에 따라 힛적용

	SetState(HIT);

}

void ElecPanda::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	PlayClip((int)state);
	

}

void ElecPanda::EndAttack()
{
	
	test2 = 0;
	test = true;
	SetState(RUN);
	Pos() = collider->GlobalPos();
	
	
}
