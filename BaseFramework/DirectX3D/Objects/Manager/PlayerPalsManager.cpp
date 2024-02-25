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

    // ��ȯ�� �縸 ������Ʈ
    if (selPal != -1)
    {
        palsMAI[pals[selPal]->name]->Update();

        pals[selPal]->Update();
    }
    

}

void PlayerPalsManager::Render()
{
    // ��ȯ�� �ȸ� Ȱ��ȭ, ��� ����(����� �� ������ ��ȯ)

    if (selPal != -1)
    {
        blendState[1]->SetState(); // ���� ����
        palsMAI[pals[selPal]->name]->Render();
        blendState[0]->SetState();

        pals[selPal]->Render();
    }
}

void PlayerPalsManager::PostRender()
{
    if (selPal != -1)
    {
        pals[selPal]->PostRender();
    }
}

void PlayerPalsManager::GUIRender()
{
}

void PlayerPalsManager::SetTarget(Transform* target)
{
    this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    // �Ƹ� �ʿ� ���� ��

    if (selPal != -1)
    {
        // ���� ��Ÿ���ϴ� ���� �߰��ϱ�
        //if () // �Ÿ������(����), ���ݴ������� ��
        pals[selPal]->SetTarget(target);
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
    if (selPal != -1)
    {
        if (pals[selPal]->GetCollider()->IsRayCollision(ray, &contact))
        {
            minDistance = contact.distance;
            hitPoint = contact.hitPoint;
        }
        
    }
    return minDistance != FLT_MAX; // �浹 Ȯ�� ������ ����
    return false; // �Ÿ� ���� �ȵǸ� �浹 ����
}

void PlayerPalsManager::OnGround(Terrain* terrain)
{
    
    if (selPal != -1)
    {
        pals[selPal]->GetTransform()->Pos().y = terrain->GetHeight(pals[selPal]->GetTransform()->GlobalPos());
    }
}

void PlayerPalsManager::InsertAllMAI()
{
    // ��Ű �� �ν��Ͻ� �ֱ�
    ModelAnimatorInstancing* pal = new ModelAnimatorInstancing("PenGuin");
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    pal->ReadClip("Work");
    pal->SetTag("Penguin");
    palsMAI.insert({ "��Ű", pal });                                     // �ִ� �� 1.
    //palsMAI.insert(pair<string, ModelAnimatorInstancing*>("��Ű", pal)); // �ִ� �� 2.
    palsMAIIndex.insert({ "��Ű", 0 }); // �� �ν��Ͻ� �ε����� map���� �߰�
                                        // "��Ű"��� key(�� �ν��Ͻ�)�� ���� �ε��� ��(0������),
                                        // ���� ���� ���� ������ �ε��� �� ����(���� ���̶� �ε����� �޶� �ٸ� ��ü)

    // �� �߰��� �߰� �۾� �� �� ----------------------
}

void PlayerPalsManager::Collision()
{
    if (selPal != -1)
    {
        // ���ǿ����� ������ ȣ��
        if (false) // ���� �´� ���� ����
        {
            pals[selPal]->Damage();
        }
    }
}

void PlayerPalsManager::Summons()
{
    if (selPal == -1) return;
    pals[selPal]->Summons(player->GlobalPos() + player->Back() * 5 ); // �ϴ��� �÷��̾� �տ� 
    // * ���� ��ǻƮ��ŷ���� ũ�ν��� ����Ű�� ������ �����ؾ� ��
}

void PlayerPalsManager::Caught(Pal* CaughtPal)
{
    // ���͸� ���� �����ؾ� ��, ����� ���� ���ϰ� ���� �����
    if (CaughtPal->name == "��Ű")
    {
        Transform* transform = palsMAI[CaughtPal->name]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Penguin(transform, palsMAI[CaughtPal->name], palsMAIIndex[CaughtPal->name]);
        // *���� ���� �Ȱ�, ���� ���� ü��, ����, ���ݷ� �� ���� �Ȱ��� �־���� �� 
        //  -> ���丮 ���� ������ �ֱ�, ����� ���� ��ü�� ���ο� �� ����

        palsMAIIndex[CaughtPal->name]++;// �ش� �� �ν��Ͻ� �ε��� ����
        pals.push_back(pal);
    }
    //else if (CaughtPal->name == "") // ���� �ٸ� ���� �ִٸ� ���⼭
    //{
    //
    //}

}
