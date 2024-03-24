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
	void SetLights();

	void SetShadowModel();

	void RenderShadowModel();

	//void SetSound();

	//QuadTreeTerrain* terrain;
	//Terrain* terrainF;
	SkyBox* skyBox;
	Water* water;

	//Player* player;
	
	// 스킬 테스트
	Skill* testSkill;

	Shadow* shadow;

	//PalBoxUi* palBoxUi;

	// UI테스트
	FieldUI* testUI;

	ModelAnimator* mam;

	// 진짜 그림자 모델 테스트
	ModelAnimator* ModelP;
	ModelAnimator* ModelM;
	ModelAnimator* ModelD;
	Model* treeS1;
	Model* treeS2;
	Model* rockS;
	Model* grassS1;
	Model* grassS2;

	// 그림자용
	BlendState* blendState[2];
	RasterizerState* rasterizer[2];

	// 파티클 테스트용
	class ParticleSystem* paTest;

};

