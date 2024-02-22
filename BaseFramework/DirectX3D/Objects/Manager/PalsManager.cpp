#include "Framework.h"

PalsManager::PalsManager()
{
    // ���⼭����
    InsertMAI("PenGuin");                   // ���� : ���̵�, �ȱ�, ��, ����, ������
    palsInstancing[0]->ReadClip("Work");    // �߰� ���

    FOR(SIZE)
    {
        Transform* transform = palsInstancing[0]->Add(); 
        transform->SetActive(false); 
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal); 
    }
    // ��������� �� �ϳ�


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
