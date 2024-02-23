#include "Framework.h"
#include "AStarScene.h"

AStarScene::AStarScene()
{
    terrain = new Terrain();
    aStar = new AStar(20, 20);
    aStar->SetNode(terrain); //������ ���߾ ��� ��ġ

    fox = new Fox();
    fox->SetTerrain(terrain);
    fox->SetAStar(aStar);
}

AStarScene::~AStarScene()
{
    delete terrain;
    delete aStar;
    delete fox;
}

void AStarScene::Update()
{
    aStar->Update();
    fox->Update();
}

void AStarScene::PreRender()
{
}

void AStarScene::Render()
{
    terrain->Render();
    aStar->Render();
    fox->Render();
}

void AStarScene::PostRender()
{
}

void AStarScene::GUIRender()
{
}