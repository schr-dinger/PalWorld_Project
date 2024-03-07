#include "Framework.h"

StructureManager::StructureManager()
{
	palBox = new PalBox();
	workBench = new WorkBench();
}

StructureManager::~StructureManager()
{
	delete palBox;
	delete workBench;
}

void StructureManager::Update()
{
	palBox->Place(PlayerManager::Get()->GetPlayer()->GetFrontPoint()->GlobalPos().x, PlayerManager::Get()->GetPlayer()->GetFrontPoint()->GlobalPos().z);
	workBench->Place(PlayerManager::Get()->GetPlayer()->GetFrontPoint()->GlobalPos().x, PlayerManager::Get()->GetPlayer()->GetFrontPoint()->GlobalPos().z);
	palBox->Update();
	workBench->Update();
}

void StructureManager::PreRender()
{
	palBox->PreRender();
	workBench->PreRender();
}

void StructureManager::Render()
{
	palBox->Render();
	workBench->Render();
}

void StructureManager::PostRender()
{
	palBox->PostRender();
	workBench->PostRender();
}

void StructureManager::GUIRender()
{
	palBox->GUIRender();
	workBench->GUIRender();
}
