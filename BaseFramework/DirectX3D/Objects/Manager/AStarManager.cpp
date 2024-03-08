#include "Framework.h"

AStarManager::AStarManager()
{
	aStar = new AStar(20, 20);
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
