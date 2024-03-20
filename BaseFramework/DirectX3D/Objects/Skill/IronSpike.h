#pragma once
class IronSpike : public Skill
{
private:

	float Life_Time = 10;


public:

	IronSpike();
	~IronSpike();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual void Setpal(class Pal* pal) override;
	virtual Collider* GetCol() override;
	virtual bool Active() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;

private:

	Vector3 startPos;
	Vector3 dir;

	Model* Spike[3];

	float time;


};

