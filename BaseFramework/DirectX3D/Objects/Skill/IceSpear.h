#pragma once
class IceSpear : public Skill
{
public:
	IceSpear();
	~IceSpear();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual bool Active() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;

	void SetHeight(Vector3 height) { this->height = height; }; // 팰마다 시작 높이 설정해주기

private:
	float speed = 10; // 나아가는 속도
	float dis = 30; // 도달하면 사라지는 거리

	Vector3 startPos;
	Vector3 dir;
	Vector3 height;

	Model* iceSpear;
	
	
	//BlendState* blendState[2];

	//RasterizerState* rasterizerState[2];
};

