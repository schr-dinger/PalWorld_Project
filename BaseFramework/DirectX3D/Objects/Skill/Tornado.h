#pragma once
class Tornado : public Skill
{
public:
	Tornado();
	~Tornado();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual void Setpal(class Pal* pal) override;
	virtual Collider* GetCol() override;
	virtual bool Active() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;

private:
	float speed = 20; // ���ư��� �ӵ�
	float dis = 20; // �����ϸ� ������� �Ÿ�

	Vector3 startPos;
	Vector3 dir;

	Model* Tornado1;
	Model* Tornado2;
	Model* Tornado3;
	Model* Tornado4;
	Model* Tornado5;


	BlendState* blendState[2];

	RasterizerState* rasterizerState[2];

	

	

};

