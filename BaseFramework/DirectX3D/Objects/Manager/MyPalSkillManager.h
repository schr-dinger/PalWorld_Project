#pragma once
class MyPalSkillManager : public Singleton<MyPalSkillManager>
{
public:
	MyPalSkillManager();
	~MyPalSkillManager();

	void Update(); // ��ų�� �ʵ忡�� ������� �� �Ŵ������� ��ų���ֱ�

	// ��ų�� ������Ʈ, ������ �� �ȿ��� ������
	bool IsCollision(Collider* collider); // ��� �÷��̾� �� ��ų �浹üũ, �������� ���
	void AddFieldSkill(Skill* skill);     // �ܺο��� �÷��̾� �� ��ų �߰����ֱ�
	
	vector<Skill*>& GetPlayerSkills() { return playerPalSkills; }

private:
	vector<Skill*> playerPalSkills; // "����" �����ϴ� �÷��̾� ���� ��ų��
};

