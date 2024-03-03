#pragma once
class BulletManager : public Singleton<BulletManager>
{
private:
	friend class Singleton;
	UINT SIZE = 10;

public:

	BulletManager();
	~BulletManager();

	void Update();
	void Render();

	void Throw(Vector3 pos, Vector3 dir);

	bool isCollision(Collider* collider);


private:

	ModelInstancing* BulletInstancing;
	vector<Bullet*> bulletes;

};

