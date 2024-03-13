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
	quad->GetMaterial()->SetDiffuseMap(tempPal->GetTextureC());
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
	if (tempPal == nullptr)
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
