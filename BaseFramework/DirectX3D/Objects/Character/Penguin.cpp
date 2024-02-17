#include "Framework.h"

Penguin::Penguin() :ModelAnimator("PenGuin")
{
    ReadClip("Idle");
    ReadClip("Walk");
    ReadClip("Run");
    ReadClip("Attack");
    ReadClip("Damage");
    ReadClip("Work");

    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);
}

Penguin::~Penguin()
{
}

void Penguin::Update()
{
    ClipSync();
    ModelAnimator::Update();
}

void Penguin::Render()
{
    ModelAnimator::Render();
}

void Penguin::GUIRender()
{
    ModelAnimator::GUIRender();
}

void Penguin::ClipSync()
{
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        PlayClip((int)action);
    }
}

void Penguin::Control()
{
}

void Penguin::Jump()
{
}
