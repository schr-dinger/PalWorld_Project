#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
	SOUND->Add("Walk", "Sounds/Action/WalkGrass.wav",false,true);
	SOUND->Add("Run", "Sounds/Action/RunGrass.wav", false, true);
	SOUND->Add("JumpLanding", "Sounds/Action/JumpLanding.wav");
	SOUND->Add("Work", "Sounds/Action/WorkBenchWork.wav", false, true);
	SOUND->Add("Build", "Sounds/Action/Hammer.wav", false, true);
	SOUND->Add("Gun_Aim", "Sounds/Action/Gun_Aim.wav");
	SOUND->Add("Gun_Draw", "Sounds/Action/Gun_Draw.wav");
	SOUND->Add("Gun_Fire", "Sounds/Action/Gun_Fire.wav");
	SOUND->Add("Gun_Reload", "Sounds/Action/Gun_Reload.wav");
	SOUND->Add("Pick_Attack", "Sounds/Action/Pick_Attack.wav", false, true);
	//SOUND->Add("Pickdraw", "Sounds/Action/pickdraw.wav");
	SOUND->Add("Pick_HitWood", "Sounds/Action/pickhit1.wav");
	//SOUND->Add("Pickhit2", "Sounds/Action/pickhit2.wav");
	SOUND->Add("Pick_HitRock", "Sounds/Action/pickhit3.wav");
}

ModelRenderScene::~ModelRenderScene()
{
   
}

void ModelRenderScene::Update()
{
    if(KEY_DOWN('1')) SOUND->PlayDelay("Walk",1,0);
    if (KEY_DOWN('2')) SOUND->Stop("Walk");
    
    

    
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    
}
