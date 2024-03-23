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

	// � �ӿ� ������ ������, �ݶ��̴� ȣ�� ��
	void Setpal(class Pal* pal) { this->pal = pal; }
	void SetEnemy(Transform* enemy) { this->enemy = enemy; }
	Collider* GetCol() { return col; }
	class Pal* Getpal() { return pal; } // �� ��ų�� � ���� ����ߴ���
	int GetDamage() { return damage; } // �� ��ų�� �������� ���
	string GetName() { return name; }  // �� ��ų�� �̸��� ����

	// ��� ��ų �� Ȱ��ȭ ����, 
	virtual bool Active() = 0;
	virtual void SetActive(bool active) = 0;
	virtual void SetSkill() = 0; //��� ��ų �� ����ġ ��Ű��
	virtual void SkillSound() = 0; // ��ų �Ҹ� ���
	virtual void SkillHitSound() = 0; // ��ų �´� �Ҹ� ���



protected:
	string name;
	int damage;
	class Pal* pal;
	Transform* enemy;
	Collider* col;

};

