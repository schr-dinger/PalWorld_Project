#pragma once
class Skill
{
public:
	Skill();
	~Skill();

	// 기본 함수들
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUIRender() = 0;

	// 어떤 팰에 세팅할 것인지, 콜라이더 호출 등
	void Setpal(class Pal* pal) { this->pal = pal; }
	void SetEnemy(Transform* enemy) { this->enemy = enemy; }
	Collider* GetCol() { return col; }
	class Pal* Getpal() { return pal; } // 이 스킬이 어떤 팰이 사용했는지
	int GetDamage() { return damage; } // 이 스킬의 데미지는 어떤지
	string GetName() { return name; }  // 이 스킬의 이름은 뭔지

	// 모든 스킬 모델 활성화 여부, 
	virtual bool Active() = 0;
	virtual void SetActive(bool active) = 0;
	virtual void SetSkill() = 0; //모든 스킬 모델 원위치 시키기
	virtual void SkillSound() = 0; // 스킬 소리 출력
	virtual void SkillHitSound() = 0; // 스킬 맞는 소리 출력



protected:
	string name;
	int damage;
	class Pal* pal;
	Transform* enemy;
	Collider* col;

};

