#pragma once
class MyPalSkillManager : public Singleton<MyPalSkillManager>
{
public:
	MyPalSkillManager();
	~MyPalSkillManager();

	void Update(); // ��ų�� �ʵ忡�� ������� �� �Ŵ������� ��ų���ֱ�

	// ��ų�� ������Ʈ, ������ �� �ȿ��� ������
	bool IsCollision(Collider* collider); // ��� �÷��̾� �� ��ų �浹üũ
	void AddFieldSkill(Skill* skill);     // �ܺο��� �÷��̾� �� ��ų �߰����ֱ�
	

private:
	vector<Skill*> PlayerPalSkills; // "����" �����ϴ� �÷��̾� ���� ��ų��
};

