#include "Framework.h"
#include "UiMouseManager.h"

UiMouseManager::UiMouseManager()
{
	quad = new Quad(size);
	tempPal = nullptr;
}

UiMouseManager::~UiMouseManager()
{
}

void UiMouseManager::SetRender()
{
	quad->GetMaterial()->SetDiffuseMap(tempPal->GetTexture());
}

void UiMouseManager::Update()
{
	quad->Pos() = mousePos + Vector3(50,-50,0);
	quad->UpdateWorld();
}

void UiMouseManager::Render()
{
	if (tempPal == nullptr)
	{
		return;
	}
	else
	{
		SetRender();
		quad->Render();
	}
}
