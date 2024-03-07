#include "Framework.h"

PlayerManager::PlayerManager()
{
	player = new Player();
}

PlayerManager::~PlayerManager()
{
	delete player;
}

void PlayerManager::Update()
{
	player->Update();
}

void PlayerManager::Render()
{
	player->Render();
}

void PlayerManager::GUIRender()
{
	player->GUIRender();
}
