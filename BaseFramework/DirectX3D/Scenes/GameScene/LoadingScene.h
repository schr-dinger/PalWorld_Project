#pragma once
class LoadingScene : public Scene
{
public:
	LoadingScene();
	~LoadingScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

public:
	thread* th;
	//float T;
	int t = 0;
	//Particle* pika;
	Quad* pika;

	bool first = false;
};