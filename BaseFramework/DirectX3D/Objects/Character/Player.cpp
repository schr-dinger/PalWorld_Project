#include "Framework.h"

Player::Player() :	ModelAnimator("Player")
{
    ReadClip("Idle");

    ReadClip("WalkF");
    ReadClip("WalkR");
    ReadClip("WalkL");

    ReadClip("RunF");
    ReadClip("RunR");
    ReadClip("RunL");

    ReadClip("Jump");

    ReadClip("Attack");

    ReadClip("Damage");

    ReadClip("Draw");
    ReadClip("Aim");
    ReadClip("Shoot");


    action = (ACTION)frameBuffer->Get().cur.clip;

    PlayClip(0);
}

Player::~Player()
{
}

void Player::Update()
{
    //ClipSync();
    ModelAnimator::Update();
}

void Player::Render()
{
    ModelAnimator::Render();
}

void Player::GUIRender()
{
    ModelAnimator::GUIRender();
}

void Player::ClipSync()
{
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        PlayClip((int)action);
    }
}

void Player::Control()
{
}

void Player::Jump()
{
}
