#pragma once
class PartyUi
{
public:
	PartyUi();
	~PartyUi();

	void Update();
	void Render();
	void PostRender();
	void GuiRender();
	void SetPal();
	void ClearModel();

private:
private:

	Vector2 Screen = { 1280.0f,720.0f };


	Quad* boxBase;
	Vector2 baseBoxSize = { 1000.0f,550.0f };

	Quad* boxBaseName;
	Vector2 boxBaseNameSize = { 300.0f,30.0f };

	Vector3 partyIconP = { 300.0f, 500.0f,0.0f };
	PartyBox* partyIcon[5];

	ModelAnimator* model;
	map<string, ModelAnimator*> models;
	string name;


	BlendState* blendState[2];
	DepthStencilState* depthState[2];

};

