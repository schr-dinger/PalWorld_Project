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
	//virtual void Setpal(class Pal* pal) override;
	//virtual Collider* GetCol() override;
	virtual bool Active() override;
	virtual void SetActive(bool active) override;
	virtual void SetSkill() override;
	virtual void SkillSound(Float3 pos) override;
	virtual void SkillHitSound(Float3 pos) override;

private:


	Model* Spike;
	ParticleSystem* particle;

	float time = 0;
	float danger = 0;
	bool Start = false;

};

