#include "Framework.h"
#include "MyPalSkillManager.h"

MyPalSkillManager::MyPalSkillManager()
{
    playerPalSkills.reserve(100); // 대충 100개 들어갈 수 있게 예약해두기

}

MyPalSkillManager::~MyPalSkillManager()
{
}

void MyPalSkillManager::Update()
{
    if (playerPalSkills.size() == 0) return; // 필드에 활성화돼있는 스킬 없으면 리턴

    for (int i = 0; i < playerPalSkills.size(); i++)
    {
        if (!playerPalSkills[i]->Active())
        {
            playerPalSkills.erase(playerPalSkills.begin() + i);
            // 스킬이 비활성화되면 vector에서 없애주기
            // 업데이트 안해주기 용도, 최적화,
        }
    }
}

bool MyPalSkillManager::IsCollision(Collider* collider)
{
    if (playerPalSkills.size() == 0) return false; // 필드에 활성화돼있는 스킬 없으면 리턴

    for (Skill* skill : playerPalSkills)
    {
        if (skill->GetCol()->IsCollision(collider))
            // 스킬이 매개변수 'collider'에 충돌했다면
        {
            if (skill->GetName() == "얼음창" )
            {
                skill->SetActive(false); // <-이 줄이 없으면 관통탄이 된다
            }
            if (skill->GetName() == "스파이크")
            {
                skill->GetCol()->SetActive(false);
            }
            //skill->SetActive(false); // <-이 줄이 없으면 관통탄이 된다

            return true;
        }

    }
    return false;
}

void MyPalSkillManager::AddFieldSkill(Skill* skill)
{
    playerPalSkills.push_back(skill);

}
