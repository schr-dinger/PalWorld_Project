#include "Framework.h"
#include "AStarManager.h"

AStarManager::AStarManager()
{
	aStar = new AStar(40, 40);
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
