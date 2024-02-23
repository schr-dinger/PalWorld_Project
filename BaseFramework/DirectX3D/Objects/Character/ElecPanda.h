#pragma once
class ElecPanda : public ModelAnimator
{

private:

	enum State
	{
		RUN,
		ATTACK,
		HIT

	};


public:

	ElecPanda();
	~ElecPanda();


	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Transform* target);

	void AI();

	void EnCounter();
	void Hit();
	void Attack();
	void Move();

	void Test(Collider* collider);

	Transform* GetTransform() { return transform; }
	CapsuleCollider* GetCollider() { return collider; }


private:

	void SetAnim();
	void SetState(State state);

	void EndAttack();



private:

	Transform* transform;
	CapsuleCollider* collider;

	
	State curState = RUN;

	Transform* target;

	Vector3 velocity;

	bool test = false;
	float test2 = 0;

};


