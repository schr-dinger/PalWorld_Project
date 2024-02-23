#include "Framework.h"
#include "QuadTreeScene.h"

QuadTreeScene::QuadTreeScene()
{
    terrain = new QuadTreeTerrain(L"Textures/HeightMaps/Hills256Height.png");
}

QuadTreeScene::~QuadTreeScene()
{
    delete terrain;
}

void QuadTreeScene::Update()
{   
}

void QuadTreeScene::PreRender()
{
}

void QuadTreeScene::Render()
{
    terrain->Render();
}

void QuadTreeScene::PostRender()
{
}

void QuadTreeScene::GUIRender()
{
    terrain->GUIRender();
}
