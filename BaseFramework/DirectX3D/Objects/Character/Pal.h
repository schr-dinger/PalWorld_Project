#pragma once
class Pal
{
public:
	enum class ACTION
	{
		IDLE,
		WALK,
		RUN,
		ATTACK,
		DAMAGE,
	};

public:
	Pal();
	~Pal();
	
	// �ڽĵ� ���� �Լ�
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ShadowRender() = 0;
	virtual void PostRender() = 0;
	virtual void GUIRender() = 0;
	virtual void SetTarget(Transform* target) = 0;
	virtual Transform* GetTransform() = 0;
	virtual CapsuleCollider* GetCollider() = 0;
	virtual Texture* GetTexture() = 0;
	virtual Texture* GetTextureC() = 0;
	virtual float GetCurHp() = 0;

	// ���� ���� ��� ���⼭ �ֱ�
	virtual void FieldAttack() = 0;
	virtual void Attack() = 0;
	virtual void Damage() = 0;
	//virtual void Die() = 0;
	// -> ��Ÿ ���...
	// �ӽ÷� ���� �߰�
	virtual void Spawn(Vector3 pos) = 0;
	// ��ȯ
	virtual void Summons(Vector3 pos) = 0;

	string GetModelName() { return modelName; }

	virtual ModelAnimatorInstancing* GetInstancing() = 0;
	Quad* GetEmote() { return emote; }
public:  // ���߰�(protected, �ڽ��� �ٷ� �� �� �ְ�) ���߿� ���Լ� ���� ��
	// �ڽĵ� ����и� ���⼭
	string name;
	string modelName;
	int level;
	//ModelAnimatorInstancing* instancing;

	// �� ���� ��ų��, ����ó�� 3��
	Skill* skill[3];

	// �� ������
	Texture* icon;
	Texture* iconC;

	Vector3 destVel;
	Vector3 velocity;
	float speed;

	// �� �������� : �� ���Ǿ �¾Ұų�, ��Ÿ ���
	bool isInvincible;

	bool isSpawned = false;
	// �� UI����
	bool isUIOn;
	float onUITime;
	float offUITime = 2.0f; // ������ �ð�

	Transform* target;

	float moveTime = 0.0f;
	Vector3 randomDir;
	float r = 5.0f;

	// 테스트 그림자:
	Sphere* shadowSphere;

	Quad* emote;

	BlendState* blendState[2];

	bool isDead = false;
};

