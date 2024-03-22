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

	//void SceneLoading();
public:
	//thread* th;
	float T;
	bool Ini = true;

	Quad* big;
};