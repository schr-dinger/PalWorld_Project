#pragma once
class Skill
{
public:
	Skill();
	~Skill();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUIRender() = 0;

	virtual void Setpal(class Pal* pal) = 0;
	virtual Collider* GetCol() = 0;

	virtual void SetActive(bool active) = 0;

protected:
	string name;
	int damage;
	class Pal* pal;
	Collider* col;

};

