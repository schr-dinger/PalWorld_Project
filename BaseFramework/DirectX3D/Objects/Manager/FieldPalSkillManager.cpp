#include "Framework.h"

FieldPalSkillManager::FieldPalSkillManager()
{
    fieldSkills.reserve(100); // ���� 100�� �� �� �ְ� �����صα�
}

FieldPalSkillManager::~FieldPalSkillManager()
{
}

void FieldPalSkillManager::Update()
{
    if (fieldSkills.size() == 0) return; // �ʵ忡 Ȱ��ȭ���ִ� ��ų ������ ����

    for (int i = 0; i < fieldSkills.size(); i++)
    {
        if (!fieldSkills[i]->Active())
        {
            fieldSkills.erase(fieldSkills.begin() + i); 
            // ��ų�� ��Ȱ��ȭ�Ǹ� vector���� �����ֱ�
            // ������Ʈ �����ֱ� �뵵, ����ȭ,
        }
    }
}

bool FieldPalSkillManager::IsCollision(Collider* collider)
{
    if (fieldSkills.size() == 0) return false; // �ʵ忡 Ȱ��ȭ���ִ� ��ų ������ ����

    for (Skill* skill : fieldSkills)
    {
        if (skill->GetCol()->IsCollision(collider)) 
            // ��ų�� �Ű����� 'collider'�� �浹�ߴٸ�
        {
            //skill->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�

            return true;
        }
        
    }
    return false;
}

void FieldPalSkillManager::AddFieldSkill(Skill* skill)
{
    fieldSkills.push_back(skill);
}
