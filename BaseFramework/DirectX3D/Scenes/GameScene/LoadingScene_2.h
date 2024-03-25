#pragma once
class LoadingScene_2 : public Scene
{
public:
	LoadingScene_2();
	~LoadingScene_2();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

public:
	thread* th;

	Vector3 middle = { 1280.0f / 2.0f,720.0f / 2.0f ,0.0f };
	Quad* titleBg;
	ProgressBar* loadingBar;

	float fakeT = 0.0f;
	bool first = false;
	bool isLoading = false;

};

