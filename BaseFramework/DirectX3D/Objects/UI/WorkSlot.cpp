#include "Framework.h"
#include "WorkSlot.h"

WorkSlot::WorkSlot(int Number)
{

	MakeSlot = new Quad(Vector2(50, 50));
	MakeSlot->Pos() = Vector3(0, 0, 0);

	
	
	// ����ġ�� ������ �ʿ��� ������ ���� �־ ����
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

	// ���� �ϳ� �޾Ƽ� �ʿ������ ������ŭ �׽�Ʈ



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
