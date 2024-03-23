#include "Framework.h"

PalSpearManager::PalSpearManager()
{
    palSpearInstancing = new ModelInstancing("PalSpear");

    //palSpears.reserve(SIZE);  // ��ť�� �ʿ����
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
    // ���� �����
        for (PalSpear* palSpear : palSpears)
            delete palSpear;

    //�𵨵� �����
    delete palSpearInstancing;
    //delete catchingPal;
}

void PalSpearManager::Update()
{
    palSpearInstancing->Update(); //�� ������Ʈ
    for (PalSpear* palSpear : palSpears) palSpear->Update(); //�����͵� ������Ʈ
}

void PalSpearManager::PreRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->PreRender();
}

void PalSpearManager::Render()
{
    palSpearInstancing->Render(); //�� Render
    for (PalSpear* palSpear : palSpears) palSpear->Render(); //�����͵� Render
                    //���� ȣ��� ����Render�� ������ �ʿ䰡 ����(�������� �浹ü ������)
}

void PalSpearManager::PostRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->PostRender();
}

void PalSpearManager::GUIRender()
{
    for (PalSpear* palSpear : palSpears) palSpear->GUIRender(); //�����͵� Render

}

void PalSpearManager::Throw(Vector3 pos, Vector3 dir)
{
    for (PalSpear* palSpear : palSpears)
    {
        //���� �� ���� ������ ó������ �Ǻ��ؼ� �ϳ��� ������ �ٷ� ����
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
            //�Ѿ��� �¾��� ��, "�Ѿ���" ������ �ڵ带 �߰�

            //���� �ڵ� : �浹 �� ������� �ϱ�
            //palSpear->GetTransform()->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
            //return true;

            // 240308 �׽�Ʈ: ����ó�� �����
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
