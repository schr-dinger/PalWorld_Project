#include "Framework.h"
#include "MyPalSkillManager.h"

MyPalSkillManager::MyPalSkillManager()
{
    playerPalSkills.reserve(100); // ���� 100�� �� �� �ְ� �����صα�

}

MyPalSkillManager::~MyPalSkillManager()
{
}

void MyPalSkillManager::Update()
{
    if (playerPalSkills.size() == 0) return; // �ʵ忡 Ȱ��ȭ���ִ� ��ų ������ ����

    for (int i = 0; i < playerPalSkills.size(); i++)
    {
        if (!playerPalSkills[i]->Active())
        {
            playerPalSkills.erase(playerPalSkills.begin() + i);
            // ��ų�� ��Ȱ��ȭ�Ǹ� vector���� �����ֱ�
            // ������Ʈ �����ֱ� �뵵, ����ȭ,
        }
    }
}

bool MyPalSkillManager::IsCollision(Collider* collider)
{
    if (playerPalSkills.size() == 0) return false; // �ʵ忡 Ȱ��ȭ���ִ� ��ų ������ ����

    for (Skill* skill : playerPalSkills)
    {
        if (skill->GetCol()->IsCollision(collider))
            // ��ų�� �Ű����� 'collider'�� �浹�ߴٸ�
        {
            if (skill->GetName() == "����â" )
            {
                skill->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
            }
            if (skill->GetName() == "������ũ")
            {
                skill->GetCol()->SetActive(false);
            }
            //skill->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�

            return true;
        }

    }
    return false;
}

void MyPalSkillManager::AddFieldSkill(Skill* skill)
{
    playerPalSkills.push_back(skill);

}
