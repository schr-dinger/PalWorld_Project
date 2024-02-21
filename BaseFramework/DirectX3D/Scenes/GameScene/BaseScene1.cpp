#include "Framework.h"
#include "BaseScene1.h"

BaseScene1::BaseScene1()
{
	player = new Player();

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("test2"); // �����信 ���� ī�޶� ��ġ ���� �ε� (������ �ε� ������ �״��)
	//CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)


	penguin = new Penguin();
	penguin->Scale() *= 0.01f;
}

BaseScene1::~BaseScene1()
{
}

void BaseScene1::Update()
{
	player->Update();
	penguin->Update();
}

void BaseScene1::PreRender()
{
}

void BaseScene1::Render()
{
	player->Render();
	penguin->Render();
}

void BaseScene1::PostRender()
{
}

void BaseScene1::GUIRender()
{
	player->GUIRender();
	penguin->GUIRender();
}
