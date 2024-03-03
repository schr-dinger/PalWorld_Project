#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    //model = new Model("Test2");

    //test = new ElecPanda();
    naruto = new Model("bow");

    naruto->Scale() *= 2.0f;

    //test->SetTarget(naruto->GetTransform());
}

ModelRenderScene::~ModelRenderScene()
{
    //delete model;
    delete test;
}

void ModelRenderScene::Update()
{

    //test->Test(naruto->GetCollider());

    //model->UpdateWorld();
    naruto->UpdateWorld();
    //test->Update();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    //model->Render();
    naruto->Render();
    //test->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    //model->GUIRender();
    //test->GUIRender();
    naruto->GUIRender();
}
