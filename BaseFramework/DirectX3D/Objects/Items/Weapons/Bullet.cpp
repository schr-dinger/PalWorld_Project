#include "Framework.h"


Bullet::Bullet(Transform* transform) : transform(transform)
{



	collider = new CapsuleCollider();
	collider->SetParent(transform);

	collider->Scale() = { 0.5,0.5,0.5 };
	collider->Pos() = {};



}

Bullet::~Bullet()
{
	delete collider;


}

void Bullet::Update()
{
	if (!transform->Active())
	{
		GForce = 0.0f;
		return;
	}
	time += DELTA;

	if (time > LIFE_SPAN)
		transform->SetActive(false);

	gravity();

	collider->UpdateWorld();


}

void Bullet::Render()
{
	//collider->Render();
}

void Bullet::Throw(Vector3 pos, Vector3 dir)
{
	transform->SetActive(true);

	transform->Pos() = pos;
	direction = dir;


	transform->Rot().y = atan2(dir.x, dir.z) + XM_PI;


	time = 0; //경과시간 리셋

}

void Bullet::gravity()
{


	GForce += 9.8f * DELTA;
	Vector3 V = ((direction + Vector3(0, 0.05f, 0)) * speed) + (Vector3(0, -1, 0) * GForce);
	// transform->Rot().x += V.y * DELTA;
	transform->Rot().x = atan2(30, V.y) + XM_PIDIV2;

	transform->Pos() += V * DELTA;


}
