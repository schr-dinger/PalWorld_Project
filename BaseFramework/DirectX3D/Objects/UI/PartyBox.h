#pragma once
class PartyBox
{
public:
	PartyBox();
	~PartyBox();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

private:
	Quad* partyBox;
};

