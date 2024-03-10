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

	//모델도 지우기
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
	BulletInstancing->Render(); //모델 Render
	for (Bullet* bullet : bulletes) bullet->Render();
	particle->Render();

}

void BulletManager::Throw(Vector3 pos, Vector3 dir)
{
	for (Bullet* bullet : bulletes)
	{
		//아직 안 던진 순번을 처음부터 판별해서 하나만 던지고 바로 종료
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
			//총알이 맞았을 때, "총알이" 수행할 코드를 추가
			particle->Play(bullet->GetCollider()->GlobalPos());


			bullet->GetTransform()->SetActive(false); // <-이 줄이 없으면 관통탄이 된다
			return true;
		}
	}

	return false;
}
