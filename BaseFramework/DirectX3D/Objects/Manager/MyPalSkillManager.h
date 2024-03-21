#pragma once
class MyPalSkillManager : public Singleton<MyPalSkillManager>
{
public:
	MyPalSkillManager();
	~MyPalSkillManager();

	void Update(); // 스킬이 필드에서 사라지면 이 매니저에서 스킬빼주기

	// 스킬의 업데이트, 랜더는 각 팔에서 실행중
	bool IsCollision(Collider* collider); // 모든 플레이어 팔 스킬 충돌체크, 누구에게 대미
	void AddFieldSkill(Skill* skill);     // 외부에서 플레이어 팔 스킬 추가해주기
	
	vector<Skill*>& GetPlayerSkills() { return playerPalSkills; }

private:
	vector<Skill*> playerPalSkills; // "현재" 존재하는 플레이어 팔의 스킬들
};

