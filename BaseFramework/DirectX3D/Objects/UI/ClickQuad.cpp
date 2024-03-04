#include "Framework.h"
#include "ClickQuad.h"

ClickQuad::ClickQuad()
{
    click = nullptr;
}

ClickQuad::~ClickQuad()
{
    delete click;
}

void ClickQuad::Update()
{
    click->Update();
}

void ClickQuad::Render()
{
    click->Render();
}

void ClickQuad::PostRender()
{
}

void ClickQuad::GuiRender()
{
}


bool ClickQuad::MouseCollision()
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

