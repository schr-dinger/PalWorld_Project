#include "Framework.h"

PalSpearManager::PalSpearManager()
{
    palSpearInstancing = new ModelInstancing("PalSpear");

    //palSpears.reserve(SIZE);  // 데큐는 필요없음
    FOR(SIZE)
    {
        Transform* transform = palSpearInstancing->Add();
        transform->SetActive(false);
        PalSpear* palSpear = new PalSpear(transform);
        palSpears.push_back(palSpear);
    }

    //palWhiteTexture = Texture::Add(L"Textures/Color/White.png");
    //catchingPal == nullptr;
}

PalSpearManager::~PalSpearManager()
{
    // 벡터 지우기
        for (PalSpear* palSpear : palSpears)
            delete palSpear;

    //모델도 지우기
    delete palSpearInstancing;
    //delete catchingPal;
}

void PalSpearManager::Update()
{
    palSpearInstancing->Update(); //모델 업데이트
    for (PalSpear* palSpear : palSpears) palSpear->Update(); //데이터도 업데이트
}

void PalSpearManager::PreRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->PreRender();
}

void PalSpearManager::Render()
{
    palSpearInstancing->Render(); //모델 Render
    for (PalSpear* palSpear : palSpears) palSpear->Render(); //데이터도 Render
                    //지금 호출된 쿠나이Render는 원래는 필요가 없다(어디까지나 충돌체 렌더용)
}

void PalSpearManager::PostRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->PostRender();
}

void PalSpearManager::GUIRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->GUIRender(); //데이터도 Render

}

void PalSpearManager::Throw(Vector3 pos, Vector3 dir)
{
    for (PalSpear* palSpear : palSpears)
    {
        //아직 안 던진 순번을 처음부터 판별해서 하나만 던지고 바로 종료
        if (!palSpear->GetTransform()->Active())
        {
            palSpear->Throw(pos, dir);
            return;
        }
    }
}

bool PalSpearManager::IsCollision(Collider* collider, class Pal* pal)
{
    for (PalSpear* palSpear : palSpears)
    {
        if (palSpear->GetCollider()->IsCollision(collider))
        {
            //총알이 맞았을 때, "총알이" 수행할 코드를 추가

            //샘플 코드 : 충돌 후 사라지게 하기
            //palSpear->GetTransform()->SetActive(false); // <-이 줄이 없으면 관통탄이 된다
            //return true;

            // 240308 테스트: 게임처럼 만들기
            palSpear->SetState(PalSpear::State::HITPAL);
            palSpear->SetPal(pal);
            palSpear->GetCollider()->SetActive(false);
            SOUND->Stop("Sphere_Hit");
            SOUND->Play("Sphere_Hit");
            return true;
        }
    }

    return false;
}

void PalSpearManager::SetTerrain(Terrain* terrain)
{
    for (PalSpear* palSpear : palSpears)
    {
        palSpear->SetTerrain(terrain);
    }
}
