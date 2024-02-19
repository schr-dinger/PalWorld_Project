#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	player = new Player();
	//penguin = new Penguin();
}

BaseScene1::~BaseScene1()
{
}

void BaseScene1::Update()
{
	player->Update();
	//penguin->Update();
}

void BaseScene1::PreRender()
{
}

void BaseScene1::Render()
{
	player->Render();
	//penguin->Render();
}

void BaseScene1::PostRender()
{
}

void BaseScene1::GUIRender()
{
	player->GUIRender();
	//penguin->GUIRender();
}
