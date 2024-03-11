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

	// Pal을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
	virtual void SetTarget(Transform* target) override;
	virtual Transform* GetTransform() override;
	virtual CapsuleCollider* GetCollider() override;
	virtual Texture* GetTexture() override { return icon; }
	virtual Texture* GetTextureC() override { return iconC; }
	virtual float GetCurHp() override;
	virtual void FieldAttack() override;
	virtual void Attack() override;
	virtual void Damage() override;
	virtual void Spawn(Vector3 pos) override;
	virtual void Summons(Vector3 pos) override;

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

	Vector3 velocity;
	UINT index;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	ProgressBar* hpBar;

	Vector3 barPos;


	ACTION action = ACTION::IDLE;
	int tmpN;

};

