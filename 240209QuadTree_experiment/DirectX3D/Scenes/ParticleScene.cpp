#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    collider = new SphereCollider(30); // �׽�Ʈ�� �浹ü

    //particle = new Spark(L"Textures/Effect/star.png", true);
    //particle = new Rain(); //�� ����
    //particle = new Sprite(L"Textures/Effect/explosion.png", 10, 10, 5, 3);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 25, 8, 2, false);

    // ��ƼŬ�� �����̰�, ������ �ƴ� ���� ����� �ʿ��� ��
    //particle->Play(Vector3()); //�������� ���� ����Ʈ ����

    //---------------------------------------

    // ���� ��ƼŬ ���
    //particle = new ParticleSystem(L"Textures/Effect/explosion.png");
                                        // �׸����� �����
    particle = new ParticleSystem("TextData/Particles/Star.fx");
                                        // ������ ������ ������ �о �����

    Penguin = new ModelAnimator("PenGuin");
    Penguin->ReadClip("Idle",0);
    Penguin->ReadClip("Walk",0);
    Penguin->ReadClip("Run",0);
    Penguin->ReadClip("Attack",0);
    Penguin->ReadClip("Damage",0);
    Penguin->ReadClip("Work",0);

    Penguin->PlayClip(0);

    FOR(2)
    {
        A[i] = new Transform();
    }

    A[0]->SetParent(A[1]);
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
    delete Penguin;
}

void ParticleScene::Update()
{
    A[1]->SetWorld(Penguin->GetTransformByNode(6));





    particle->Play(A[0]->GlobalPos()+Vector3(0,75,0)); //�ű⼭ ��ƼŬ ���
    FOR(2)
    {
        A[i]->UpdateWorld();
    }

    Penguin->Update();
    particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();

    Penguin->Render();

}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    particle->GUIRender();
}
