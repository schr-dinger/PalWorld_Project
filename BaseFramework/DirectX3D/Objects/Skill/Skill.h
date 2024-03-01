#pragma once
class Skill
{
public:
	Skill();
	~Skill();

	// �⺻ �Լ���
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUIRender() = 0;

	// � �ӿ� ������ ������, �ݶ��̴� ȣ��
	virtual void Setpal(class Pal* pal) = 0;
	virtual Collider* GetCol() = 0;

	// ��� ��ų �� Ȱ��ȭ ����, 
	virtual bool Active() = 0;
	virtual void SetActive(bool active) = 0;
	virtual void SetSkill() = 0; //��� ��ų �� ����ġ ��Ű��

protected:
	string name;
	int damage;
	class Pal* pal;
	Collider* col;

};

