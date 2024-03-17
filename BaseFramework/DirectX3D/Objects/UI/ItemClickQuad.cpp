#include "Framework.h"

ItemClickQuad::ItemClickQuad()
{
	click = new Quad(size);
	click->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");

	item = nullptr;
}

ItemClickQuad::~ItemClickQuad()
{
	delete click;
	delete item;
}

void ItemClickQuad::Update()
{
	click->Update();

	//


}

void ItemClickQuad::Render()
{
	click->Render();
	if (MouseCollision() && GetItem() != nullptr && GetItem()->type == Item::Type::INGREDIENT)
	{
		int a = ItemManager::Get()->GetItemDV()[GetItem()->num].second;
		string b = to_string(a);
		Font::Get()->RenderText(b, Vector2(click->Pos().x, click->Pos().y));
	}
}

void ItemClickQuad::PostRender()
{
}

void ItemClickQuad::GuiRender()
{
}

void ItemClickQuad::SetTexture()
{
	if (item == nullptr)
	{
		click->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass.png");
	}
	else
	{
		//click->GetMaterial()->SetDiffuseMap(L"Textures/UI/PalIcon/T_Penguin_icon_normal.png");
		click->GetMaterial()->SetDiffuseMap(item->GetTexture());
	}
}

bool ItemClickQuad::MouseCollision()
{
	float minX = click->Pos().x - click->GetSize().x * 0.5f;
	float maxX = click->Pos().x + click->GetSize().x * 0.5f;
	float minY = click->Pos().y - click->GetSize().y * 0.5f;
	float maxY = click->Pos().y + click->GetSize().y * 0.5f;

	if (minX < mousePos.x && maxX > mousePos.x && minY < mousePos.y && maxY > mousePos.y)
	{
		return true;
	}

	return false;
}

bool ItemClickQuad::Check(int Num)
{
	if (ItemManager::Get()->GetItemV()[Num].back()->type == GetItem()->type
		&& ItemManager::Get()->GetItemV()[Num].back()->num == GetItem()->num) return true;


	return false;
}
