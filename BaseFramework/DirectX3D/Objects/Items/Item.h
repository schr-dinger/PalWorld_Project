#pragma once
class Item // : public GameObject
{

public:

	enum Type
	{
		WEAPON, INGREDIENT
	};

public:

	Item();
	~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;
	//virtual void PostRender() = 0;
	virtual Texture* GetTexture() = 0;
	virtual Model* GetModel() = 0;

	// virtual void SetActive() = 0;


public:

	//string name;	
	int num;
	Type type;

	Texture* icon;
	Model* test;


};

