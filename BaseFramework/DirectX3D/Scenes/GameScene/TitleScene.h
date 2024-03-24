#pragma once
class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
	

private:
	Vector3 middle = { 1280.0f / 2.0f,720.0f / 2.0f ,0.0f };
	Quad* titleBg;
	Quad* title;
	Quad* titleShadow;

	ClickQuad* gameStart;
	ClickQuad* gameExit;
	Vector2 clickSize = { 300.0f,50.0f };

	int initCount = 0;
	bool isGrowing = true;
	bool keySound[2];
	//BlendState* blendState[2];
};