#include "Framework.h"

PlayerPalsManager::PlayerPalsManager()
{
    terrain = nullptr;
    target = nullptr;

    selPal = -1;

    InsertAllMAI(); // ��� �� �� �ν��Ͻ� ����

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
}

PlayerPalsManager::~PlayerPalsManager()
{
    for (Pal* pal : pals)
        delete pal;

    FOR(2)
        delete blendState[i];
}

void PlayerPalsManager::Update()
{
    OnGround(terrain);

    // �浹 ���� ����
    Collision();

    // �� ������Ʈ
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal���� ������ ����������, 
                       // ����ȵǸ� �⺻ �Լ��� �ٲٱ�
}

void PlayerPalsManager::Render()
{
    blendState[1]->SetState(); // ���� ����
    for (map<string, ModelAnimatorInstancing*>::iterator iter = palsMAI.begin(); iter != palsMAI.end(); iter++)
        iter->second->Render();
    blendState[0]->SetState();

    for (Pal* pal : pals)
    {
        //if (pal->acti)
        //{
        //
        //}
        pal->Render();

    }
}

void PlayerPalsManager::PostRender()
{
    // ĳ���� UI����
    for (Pal* pal : pals)
        pal->PostRender();
}

void PlayerPalsManager::GUIRender()
{
}

void PlayerPalsManager::SetTarget(Transform* target)
{
    this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    //�� �κ� ���忡���� ǥ���� ���� ����
    for (Pal* pal : pals)
    {
        // ���� ��Ÿ���ϴ� ���� �߰��ϱ�
        //if () // �Ÿ������(����), ���ݴ������� ��
        pal->SetTarget(target);
    }

}

void PlayerPalsManager::SetPlayer(Player* player)
{
    player = this->player;
}

bool PlayerPalsManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    Contact contact;
    float minDistance = FLT_MAX;
    for (Pal* pal : pals)
    {
        //�ܺο��� �� ������ �κ��� �浹�ϸ�...
        if (pal->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //�κ����� ���� ���� ��� ����
            {
                minDistance = contact.distance; // �������� ��� �ݿ�
                hitPoint = contact.hitPoint;
            }
        }
    }
    return minDistance != FLT_MAX; // �浹 Ȯ�� ������ ����
    return false; // �Ÿ� ���� �ȵǸ� �浹 ����
}

void PlayerPalsManager::OnGround(Terrain* terrain)
{
    for (Pal* pal : pals)
    {
        pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
    }
}

void PlayerPalsManager::InsertAllMAI()
{
}

void PlayerPalsManager::Collision()
{
    for (Pal* pal : pals)
    {
        // ���ǿ����� ������ ȣ��
        if (false) // 
        {
            pal->Damage();
            return;
        }
    }
}

void PlayerPalsManager::Summons()
{
    if (selPal == -1) return;
    pals[selPal]->Summons(player->GlobalPos() + player->Back() * 5 ); // �ϴ��� �÷��̾� �տ� 
    // * ���� ��ǻƮ��ŷ���� ũ�ν��� ����Ű�� ������ �����ؾ� ��
}
