#include "Framework.h"
#include "AStarManager.h"

AStarManager::AStarManager()
{
	aStar = new AStar(50, 50);
	aStar->SetNode(LandScapeManager::Get()->GetTerrain());
}

AStarManager::~AStarManager()
{
	delete aStar;
}

void AStarManager::Update()
{
	aStar->Update();
}

void AStarManager::Render()
{
	aStar->Render();
}
