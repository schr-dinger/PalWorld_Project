#pragma once
class Equipment : public Item
{

public:

	Equipment(int Num);
	~Equipment();

	void Update();
	void Render();

	// void Equip();

	Transform* GetTransform() { return transform; }
	Texture* GetTexture() { return icon; }
	Model* GetModel() { return test; }

	//Transform* GetCollider() { return collider; }

private:


	Transform* transform;
	SphereCollider* collider;


};

