#pragma once
class Tornado : public Skill
{
public:
	Tornado();
	~Tornado();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual void Setpal(class Pal* pal) override;
	virtual Collider* GetCol() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;

private:
	float speed = 5; // 나아가는 속도
	float dis = 20; // 도달하면 사라지는 거리

	Model* Tornado1;
	Model* Tornado2;
	Model* Tornado3;
	Model* Tornado4;
	Model* Tornado5;


	BlendState* blendState[2];

	RasterizerState* rasterizerState[2];

	

	

};

