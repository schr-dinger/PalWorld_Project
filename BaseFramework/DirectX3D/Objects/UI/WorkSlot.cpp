#include "Framework.h"
#include "WorkSlot.h"

WorkSlot::WorkSlot(int Number)
{

	MakeSlot = new Quad(Vector2(50, 50));
	MakeSlot->Pos() = Vector3(0, 0, 0);

	
	
	// 스위치로 돌려서 필요한 아이템 수를 넣어서 돌려
	switch (Number)
	{
	case 0:
		test = new WorkInFo(1, 2);
		//test = new WorkInFo(2, 2);
	case 1:
		test = new WorkInFo(1, 3);

		break;
	case 2:
		test = new WorkInFo(1, 3);
		break;
	case 3:
		test = new WorkInFo(1, 3);
		break;
	case 4:
		test = new WorkInFo(1, 3);
		break;
	case 5:
		test = new WorkInFo(1, 3);
		break;
	default:



	}

	// 변수 하나 받아서 필요아이템 갯수만큼 테스트



}

WorkSlot::~WorkSlot()
{
}

void WorkSlot::Update()
{
}

void WorkSlot::Render()
{
}

void WorkSlot::PostRender()
{
}

void WorkSlot::GUIRender()
{
}

bool WorkSlot::MouseCollision()
{

	float minX = MakeSlot->Pos().x - MakeSlot->GetSize().x * 0.5f;
	float maxX = MakeSlot->Pos().x + MakeSlot->GetSize().x * 0.5f;
	float minY = MakeSlot->Pos().y - MakeSlot->GetSize().y * 0.5f;
	float maxY = MakeSlot->Pos().y + MakeSlot->GetSize().y * 0.5f;

	if (minX < mousePos.x && maxX > mousePos.x && minY < mousePos.y && maxY > mousePos.y)
	{
		return true;
	}

	return false;


	
}
