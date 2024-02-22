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

    FOR(2)
    {
        blendState[i] = new BlendState();
    }
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);

    SetTag("P");
    Scale() *= 0.01f;
}

Penguin::~Penguin()
{
}

void Penguin::Update()
{
    //ClipSync();
    ModelAnimator::Update();
}

void Penguin::Render()
{
    blendState[1]->SetState();
    ModelAnimator::Render();
    blendState[0]->SetState();

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
