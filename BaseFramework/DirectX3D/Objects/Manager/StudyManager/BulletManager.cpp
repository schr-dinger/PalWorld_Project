#include "Framework.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	BulletInstancing = new ModelInstancing("bow");
	particle = new ParticleSystem("TextData/Particles/Star.fx");


	bulletes.reserve(SIZE);
	FOR(SIZE)
	{
		Transform* transform = BulletInstancing->Add();
		transform->SetActive(false);
		Bullet* bullet = new Bullet(transform);
		bulletes.push_back(bullet);

	}

}

BulletManager::~BulletManager()
{
	for (Bullet* bullet : bulletes)
		delete bullet;

	//�𵨵� �����
	delete BulletInstancing;

}

void BulletManager::Update()
{
	BulletInstancing->Update();
	for (Bullet* bullet : bulletes) bullet->Update();
	particle->Update();


}

void BulletManager::Render()
{
	BulletInstancing->Render(); //�� Render
	for (Bullet* bullet : bulletes) bullet->Render();
	particle->Render();

}

void BulletManager::Throw(Vector3 pos, Vector3 dir)
{
	for (Bullet* bullet : bulletes)
	{
		//���� �� ���� ������ ó������ �Ǻ��ؼ� �ϳ��� ������ �ٷ� ����
		if (!bullet->GetTransform()->Active())
		{
			bullet->Throw(pos, dir);
			return;
		}
	}

}

bool BulletManager::isCollision(Collider* collider)
{
	for (Bullet* bullet : bulletes)
	{
		if (bullet->GetCollider()->IsCollision(collider))
		{
			//�Ѿ��� �¾��� ��, "�Ѿ���" ������ �ڵ带 �߰�
			particle->Play(bullet->GetCollider()->GlobalPos());


			bullet->GetTransform()->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
			return true;
		}
	}

	return false;
}
