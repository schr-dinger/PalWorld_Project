#pragma once
class FieldPalSkillManager : public Singleton<FieldPalSkillManager>
{
	// �ʵ� ���� ��ų ����, �ܺο��� �浹�� üũ�ϱ� ���� Ŭ����
	// ex. �ʵ� "��Ű"�� ��ų ����, ���� �� �Ŵ������� �� Ŭ������ �ҷ��� ��ųüũ

public:
	FieldPalSkillManager();
	~FieldPalSkillManager();

	void Update(); // ��ų�� �ʵ忡�� ������� �� �Ŵ������� ��ų���ֱ�

	// ��ų�� ������Ʈ, ������ �� �ȿ��� ������
	bool IsCollision(Collider* collider); // ��� �ʵ� �� ��ų �浹üũ
	void AddFieldSkill(Skill* skill);                 // �ܺο��� �ʵ� ��ų �߰����ֱ�
	// ex. �ʵ� "��Ű"�� ��ų ����, 'AddFieldSkill()'�� �ش� ��ų ���⿡ �߰����ְ�,
	//     �÷��̾� Ȥ�� �����ȸŴ������� IsCollision()�� �ҷ��� �浹üũ

	vector<Skill*>& GetFieldSkills() { return fieldSkills; }

private:
	vector<Skill*> fieldSkills; // "����" �����ϴ� �ʵ� ���� ��ų��
};

