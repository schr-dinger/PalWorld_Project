#include "Framework.h"
#include "UiMouseManager.h"

UiMouseManager::UiMouseManager()
{
	quad = new Quad(size);
	quadBack = new Quad(size);
	quadBack->GetMaterial()->SetDiffuseMap(L"Textures/Color/BlackGlass50_C.png");
	tempPal = nullptr;
}

UiMouseManager::~UiMouseManager()
{
}

void UiMouseManager::SetRender()
{
	if (tempPal != nullptr)
	{
		quad->GetMaterial()->SetDiffuseMap(tempPal->GetTextureC());
	}
	else if (tempItem != nullptr)
	{
		quad->GetMaterial()->SetDiffuseMap(tempItem->GetTexture());
	}
}

void UiMouseManager::Update()
{
	quad->Pos() = mousePos + Vector3(50,-50,0);
	quadBack->Pos() = mousePos + Vector3(50,-50,0);
	quad->UpdateWorld();
	quadBack->UpdateWorld();
}

void UiMouseManager::Render()
{
	if (tempPal == nullptr &&tempItem == nullptr)
	{
		return;
	}
	else
	{
		SetRender();
		quadBack->Render();
		quad->Render();
	}
}
