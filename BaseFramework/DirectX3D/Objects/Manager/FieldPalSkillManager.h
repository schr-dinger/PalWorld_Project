#pragma once
class FieldPalSkillManager : public Singleton<FieldPalSkillManager>
{
	// 필드 팔이 스킬 사용시, 외부에서 충돌을 체크하기 위한 클래스
	// ex. 필드 "펭키"가 스킬 사용시, 마이 팔 매니저에서 이 클래스를 불러와 스킬체크

public:
	FieldPalSkillManager();
	~FieldPalSkillManager();

	void Update(); // 스킬이 필드에서 사라지면 이 매니저에서 스킬빼주기

	// 스킬의 업데이트, 랜더는 각 팔에서 실행중
	bool IsCollision(Collider* collider); // 모든 필드 팔 스킬 충돌체크
	void AddFieldSkill(Skill* skill);                 // 외부에서 필드 스킬 추가해주기
	// ex. 필드 "펭키"가 스킬 사용시, 'AddFieldSkill()'로 해당 스킬 여기에 추가해주고,
	//     플레이어 혹은 마이팔매니저에서 IsCollision()을 불러와 충돌체크

	vector<Skill*>& GetFieldSkills() { return fieldSkills; }

private:
	vector<Skill*> fieldSkills; // "현재" 존재하는 필드 팔의 스킬들
};

