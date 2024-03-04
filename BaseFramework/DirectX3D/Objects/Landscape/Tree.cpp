#include "Framework.h"

Tree::Tree(Transform* transform) :transform(transform)
{
	collider = new CapsuleCollider();

	collider->SetParent(transform);
	collider->Scale() *= 100.0f;
	collider->Rot().x = XM_PIDIV2;
}

Tree::~Tree()
{
	delete collider;
}

void Tree::Update()
{
	if (!transform->Active()) return;
	
	if (Hp < 0.0f)
	{
		transform->SetActive(false);
	}

	transform->UpdateWorld();
	collider->UpdateWorld();
}

void Tree::Render()
{
	if (!transform->Active()) return;

	collider->Render();
}

void Tree::GUIRender()
{
}

//void Tree::Place(Transform* transform)
//{
//}

void Tree::Hit()
{
	Hp -= 20.0f;
}
