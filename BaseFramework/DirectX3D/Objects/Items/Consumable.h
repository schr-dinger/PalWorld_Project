#pragma once
class Consumable : public Item
{

private:

	float LIFE_SPAN = 5;

public:

	Consumable(int num);
	~Consumable();

	void Update();
	void Render();


	Transform* GetTransform() {}
	CapsuleCollider* GetCollider() {}
	Texture* GetTexture() { return icon; }
	Model* GetModel() { return test; }
	//void SetTerrain(class Terrain* terrain) { this->terrain = terrain; }

	void SetPos(Transform* transform);
	void SetActive();

	bool isColPlayer();


private:

	//Transform* transform;
	//CapsuleCollider* collider;

	//Terrain* terrain;

	float time;



};

