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

	void Collision();

private:
	Quad* partyBox;
};

