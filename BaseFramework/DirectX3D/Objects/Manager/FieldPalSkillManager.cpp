#include "Framework.h"

FieldPalSkillManager::FieldPalSkillManager()
{
    fieldSkills.reserve(100); // 대충 100개 들어갈 수 있게 예약해두기
}

FieldPalSkillManager::~FieldPalSkillManager()
{
}

void FieldPalSkillManager::Update()
{
    if (fieldSkills.size() == 0) return; // 필드에 활성화돼있는 스킬 없으면 리턴

    for (int i = 0; i < fieldSkills.size(); i++)
    {
        if (!fieldSkills[i]->Active())
        {
            fieldSkills.erase(fieldSkills.begin() + i); 
            // 스킬이 비활성화되면 vector에서 없애주기
            // 업데이트 안해주기 용도, 최적화,
        }
    }
}

bool FieldPalSkillManager::IsCollision(Collider* collider)
{
    if (fieldSkills.size() == 0) return false; // 필드에 활성화돼있는 스킬 없으면 리턴

    for (Skill* skill : fieldSkills)
    {
        if (skill->GetCol()->IsCollision(collider)) 
            // 스킬이 매개변수 'collider'에 충돌했다면
        {
            //skill->SetActive(false); // <-이 줄이 없으면 관통탄이 된다

            return true;
        }
        
    }
    return false;
}

void FieldPalSkillManager::AddFieldSkill(Skill* skill)
{
    fieldSkills.push_back(skill);
}
