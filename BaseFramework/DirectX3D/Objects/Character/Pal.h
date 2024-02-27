#pragma once
class Pal
{
public:
	Pal();
	~Pal();
	
	// 자식들 공통 함수
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void GUIRender() = 0;
	virtual void SetTarget(Transform* target) = 0;
	virtual Transform* GetTransform() = 0;
	virtual CapsuleCollider* GetCollider() = 0;

	// 팰의 공통 모션 여기서 넣기
	//virtual void Atack() = 0;
	virtual void Damage() = 0;
	//virtual void Die() = 0;
	// -> 기타 등등...
	// 임시로 스폰 추가
	virtual void Spawn(Vector3 pos) = 0;
	// 소환
	virtual void Summons(Vector3 pos) = 0;


public:  // 감추고(protected, 자식은 바로 쓸 수 있게) 나중에 겟함수 만들어도 됨
	// 자식들 공통분모 여기서
	string name;
};

