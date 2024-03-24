#pragma once
class IceSpear : public Skill
{
public:
	IceSpear();
	~IceSpear();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual bool Active() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;
	virtual void SkillSound(Float3 pos) override;
	virtual void SkillHitSound(Float3 pos) override;

	void SetHeight(Vector3 height) { this->height = height; }; // �Ӹ��� ���� ���� �������ֱ�

private:
	float speed = 10; // ���ư��� �ӵ�
	float dis = 20; // �����ϸ� ������� �Ÿ�

	Vector3 startPos;
	Vector3 dir;
	Vector3 height;

	Model* iceSpear;
	
	
	//BlendState* blendState[2];

	//RasterizerState* rasterizerState[2];
};

