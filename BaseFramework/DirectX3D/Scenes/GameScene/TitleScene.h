#pragma once
class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;


private:
	Quad* title;
	int initCount = 0;
};

