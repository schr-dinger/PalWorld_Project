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

	// 어떤 팰에 세팅할 것인지, 콜라이더 호출
	virtual void Setpal(class Pal* pal) = 0;
	virtual Collider* GetCol() = 0;

	// 모든 스킬 모델 활성화 여부, 
	virtual bool Active() = 0;
	virtual void SetActive(bool active) = 0;
	virtual void SetSkill() = 0; //모든 스킬 모델 원위치 시키기

protected:
	string name;
	int damage;
	class Pal* pal;
	Collider* col;

};

