#pragma once
class Bullet
{

private:

	float LIFE_SPAN = 5;

public:

	Bullet(Transform* transform);
	~Bullet();


	void Update();
	void Render();

	void Throw(Vector3 pos, Vector3 dir);

	CapsuleCollider* GetCollider() { return collider; }
	Transform* GetTransform() { return transform; }

private:

	void gravity();


private:


	Transform* transform;
	CapsuleCollider* collider;

	float speed = 15;
	float time = 0;

	Vector3 direction;

	float GForce = 0.0f;

};

