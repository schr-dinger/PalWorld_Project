#pragma once
class Pal
{
public:
	Pal();
	~Pal();
	
	// �ڽĵ� ���� �Լ�
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void GUIRender() = 0;
	virtual void SetTarget(Transform* target) = 0;
	virtual Transform* GetTransform() = 0;
	virtual CapsuleCollider* GetCollider() = 0;

	// ���� ���� ��� ���⼭ �ֱ�
	//virtual void Atack() = 0;
	virtual void Damage() = 0;
	//virtual void Die() = 0;
	// -> ��Ÿ ���...
	// �ӽ÷� ���� �߰�
	virtual void Spawn(Vector3 pos) = 0;


protected:
	// �ڽĵ� ����и� ���⼭
};

