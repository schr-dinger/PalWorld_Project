#pragma once
class BaseScene1 : public Scene
{
public:
	BaseScene1();
	~BaseScene1();

	// Scene에서 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	QuadTreeTerrain* terrain;
	//Terrain* terrainF;
	SkyBox* skyBox;
	Water* water;

	Player* player;
	
	PalBox* ice;

	// 스킬 테스트
	Skill* testSkill;

	PalBox* palBox;

};

