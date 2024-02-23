#include "Framework.h"

PalsManager::PalsManager()
{
    // ���⼭����
    InsertMAI("PenGuin");                   // ���� : ���̵�, �ȱ�, ��, ����, ������
    palsInstancing[0]->ReadClip("Work");    // �߰� ���
    palsInstancing[0]->SetTag("Penguin");

    FOR(SIZE)
    {
        Transform* transform = palsInstancing[0]->Add();
        transform->SetActive(false);
        transform->Scale() *= 0.01;// ������ ������ ���⼭
        Pal* pal = new Penguin(transform, palsInstancing[0], i);
        pals.push_back(pal);
    }
    // ��������� �� �ϳ�

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
}

PalsManager::~PalsManager()
{
    for (ModelAnimatorInstancing* pal : palsInstancing)
        delete pal;


    for (Pal* pal : pals)
        delete pal;

    FOR(2)
        delete blendState[i];
}

void PalsManager::Update()
{
    OnGround(terrain);

    // �浹 ���� ����
    Collision();

    // ������
    time += DELTA; //����ð� ����

    if (time >= SPAWN_TIME) //��� �ð��� �������ݿ� �����ϸ�
    {
        time -= SPAWN_TIME;
        Spawn(); //����(����)
    }

    // �� ������Ʈ
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Update();

    for (Pal* pal : pals)
        pal->Update(); // pal���� ������ ����������, 
                       // ����ȵǸ� �⺻ �Լ��� �ٲٱ�

    
}

void PalsManager::Render()
{
    blendState[1]->SetState(); // ���� ����
    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->Render();
    blendState[0]->SetState();

    for (Pal* pal : pals)
        pal->Render();

}

void PalsManager::PostRender()
{
    // ĳ���� UI����
    for (Pal* pal : pals)
        pal->PostRender();
}

void PalsManager::GUIRender()
{
    for (Pal* pal : pals)
        pal->GUIRender();

    for (ModelAnimatorInstancing* pal : palsInstancing)
        pal->GUIRender();

}

void PalsManager::SetTarget(Transform* target)
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

bool PalsManager::IsCollision(Ray ray, Vector3& hitPoint)
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

void PalsManager::OnGround(Terrain* terrain)
{
    for (Pal* pal : pals)
    {
        //pal->GetTransform()->Pos().y = terrain->GetHeightCompute(pal->GetTransform()->GlobalPos());
        pal->GetTransform()->Pos().y = terrain->GetHeight(pal->GetTransform()->GlobalPos());
    }
}

void PalsManager::InsertMAI(string palModelName)
{
    ModelAnimatorInstancing* pal = new ModelAnimatorInstancing(palModelName);
    //pal->Scale() *= 0.01f;
    pal->ReadClip("Idle");
    pal->ReadClip("Walk");
    pal->ReadClip("Run");
    pal->ReadClip("Attack");
    pal->ReadClip("Damage");
    palsInstancing.push_back(pal);
}

void PalsManager::Collision()
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

void PalsManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    //�����Ÿ� ����� �Բ� ǥ���� �������� ������ �Ѵ�
    Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 30);
    randomPos.y = 0;

    // ������ ������ ���� ��ҿ��� �κ� �ϳ� ���� (������)
    for (Pal* pal : pals)
    {
        if (!pal->GetTransform()->Active()) // �κ��� ��ȸ ���ε� ��Ȱ��ȭ ���� ��ü�� ������
        {
            pal->Spawn(randomPos); // ���� �κ� ȣ��
            return; //�ݺ���(���� ����) ����
        }
    }
}
