#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    //model = new Model("Test2");

    test = new ElecPanda();
    naruto = new Naruto();

    naruto->Scale() *= 0.01f;

    test->SetTarget(naruto->GetTransform());
}

ModelRenderScene::~ModelRenderScene()
{
    //delete model;
    delete test;
}

void ModelRenderScene::Update()
{

    test->Test(naruto->GetCollider());

    //model->UpdateWorld();
    naruto->Update();
    test->Update();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    //model->Render();
    naruto->Render();
    test->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    //model->GUIRender();
    test->GUIRender();
}
