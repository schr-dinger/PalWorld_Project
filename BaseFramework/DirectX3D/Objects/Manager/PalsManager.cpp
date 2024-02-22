#include "Framework.h"

PalsManager::PalsManager()
{
    // 여기서부터
    InsertMAI("PenGuin");                   // 공용 : 아이들, 걷기, 런, 공격, 데미지
    palsInstancing[0]->ReadClip("Work");    // 추가 모션

    FOR(SIZE)
    {
        Transform* transform = palsInstancing[0]->Add(); 
        transform->SetActive(false); 
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal); 
    }
    // 여기까지가 팔 하나


}

PalsManager::~PalsManager()
{
}

void PalsManager::Update()
{
}

void PalsManager::Render()
{
}

void PalsManager::PostRender()
{
}

void PalsManager::SetTarget(Transform* target)
{
}

bool PalsManager::IsCollision(Ray ray, Vector3& hitPoint)
{
	return false;
}

void PalsManager::InsertMAI(string palModelName)
{
    ModelAnimatorInstancing* pal = new ModelAnimatorInstancing(palModelName);
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    palsInstancing.push_back(pal);
}

void PalsManager::Collision()
{
}

void PalsManager::Spawn()
{
}
