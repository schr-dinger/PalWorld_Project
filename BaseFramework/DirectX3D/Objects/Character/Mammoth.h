#pragma once
class Mammoth : public Pal
{
private:
	enum class ACTION
	{
		IDLE,
		WALK,
		RUN,
		ATTACK,
		DAMAGE,
	};

public:
	Mammoth(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~Mammoth();

    void Update();
    void Render();
    void ShadowRender();
    void PostRender();
    void GUIRender();
    Texture* GetTexture() { return icon; }
    Texture* GetTextureC() { return iconC; }
    float GetCurHp() { return curHP / maxHP; }

    // 액션 : 공격
    void Attack();      // 내 팔 공격
    void FieldAttack(); // 필드 팔 공격

    // 액션 : 얻어맞기
    void Damage();

    // 액션 : 생성되기
    void Spawn(Vector3 pos);

    // 소환하기 : 플레이어가 팔 소환용
    void Summons(Vector3 pos);


    //표적 설정
    void SetTarget(Transform* target);

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }
    ModelAnimatorInstancing* GetInstancing() { return instancing; }


private:

    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    // 동작 끝나면 실행하는 함수(소환, 사망 모션 필요)
    void EndAttack();
    void EndDamage(); // Hit 였으나 enum과 명칭 일치시키기

    void SetAction(ACTION action);

    void Move();
    void MoveP();
    void MoveWithOutTarget();

    void UpdateUI();

private:
	Transform* transform;
	CapsuleCollider* collider;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* root;
	Transform* target;

	float speed;
	float maxHP;
	float curHP;

	UINT index;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;


	Vector3 barPos;


	ACTION action = ACTION::IDLE;
    int tmpN;


   

};

