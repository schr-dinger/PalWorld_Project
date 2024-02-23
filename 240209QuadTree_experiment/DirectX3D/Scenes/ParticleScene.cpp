#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    collider = new SphereCollider(30); // 테스트용 충돌체

    //particle = new Spark(L"Textures/Effect/star.png", true);
    //particle = new Rain(); //비 생성
    //particle = new Sprite(L"Textures/Effect/explosion.png", 10, 10, 5, 3);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 25, 8, 2, false);

    // 파티클이 개별이고, 조건이 아닌 수동 재생이 필요할 때
    //particle->Play(Vector3()); //원점에서 날씨 이펙트 실행

    //---------------------------------------

    // 범용 파티클 사용
    //particle = new ParticleSystem(L"Textures/Effect/explosion.png");
                                        // 그림으로 만들기
    particle = new ParticleSystem("TextData/Particles/Star.fx");
                                        // 사전에 설정된 파일을 읽어서 만들기

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





    particle->Play(A[0]->GlobalPos()+Vector3(0,75,0)); //거기서 파티클 재생
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
