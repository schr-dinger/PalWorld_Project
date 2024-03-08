#include "Framework.h"
#include "TerrainLODScene.h"

TerrainLODScene::TerrainLODScene()
{
    lod = new TerrainLOD(L"Textures/HeightMaps/ColorMap256.png");
}

TerrainLODScene::~TerrainLODScene()
{
    delete lod;
}

void TerrainLODScene::Update()
{
}

void TerrainLODScene::PreRender()
{
}

void TerrainLODScene::Render()
{
    lod->Render();
}

void TerrainLODScene::PostRender()
{
}

void TerrainLODScene::GUIRender()
{
    lod->GUIRender();
}
