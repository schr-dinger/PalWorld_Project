#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    background = new Model("Forest");
    background->SetShader(L"Basic/Texture.hlsl");
    background->Scale() *= 10.0f;
    background->UpdateWorld();

    naruto = new Naruto();

    //// �κ��� ����(��) ����
    //robotInstancing = new ModelAnimatorInstancing("Robot");
    //robotInstancing->ReadClip("StandUp");
    //robotInstancing->ReadClip("Walk");
    //robotInstancing->ReadClip("Run");
    //robotInstancing->ReadClip("Hit");
    //robotInstancing->ReadClip("Dying");
    //
    ////�κ� ���� ������ ����
    //Transform* t = robotInstancing->Add(); // ���� ����ϱ� ���� Ʈ�������� �ν��Ͻ̿��� �߰�
    //robot = new Robot(t, robotInstancing, 0); //���� �κ��� ��¿� Ʈ�������� �ε��� �ֱ�
    ////->�̷ν� �κ��� ���� ������(�κ� Ŭ����)��, ����(��)��, �� ���� �̾��� Ʈ������(t)�� �� ���´�

    //robot->SetTarget(naruto);

    KunaiManager::Get(); // �ƹ��͵� �� �ϴ� �ǹ̾��� �ڵ�����,
                         // �� �ڵ尡 ����Ǹ鼭 �̱����� �����ȴٴ� ���� ����
    
    RobotManager::Get()->SetTarget(naruto); //�̱��� ���� ��, ǥ�� ��������

    //CAM->SetTarget(naruto); //�ȷο�ķ + ������� ����
    //CAM->TargetOptionLoad("Naruto"); // �����信 ���� ī�޶� ��ġ ���� �ε� (������ �ε� ������ �״��)
    //CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->AlphaToCoverage(true); // ���� Ȥ�� ������ ������ �ܺ� �ȼ��� ������ ���ΰ�


    skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
}

GameScene::~GameScene()
{
    delete naruto;
    delete background;
    delete skyBox;

    FOR(2)
        delete blendState[i];

    KunaiManager::Get()->Delete();
    RobotManager::Get()->Delete();
}

void GameScene::Update()
{
    naruto->Update();
    //robotInstancing->Update();
    //robot->Update();

    KunaiManager::Get()->Update();
    RobotManager::Get()->Update();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
    skyBox->Render();

    blendState[1]->SetState(); // ���� �����ϱ�
    background->Render();      // ���� ����� ���¿��� ��游 ����ϱ�
    blendState[0]->SetState(); // ���� �����ϱ�

    naruto->Render();
    //robotInstancing->Render();
    //robot->Render();

    KunaiManager::Get()->Render();
    RobotManager::Get()->Render();
}

void GameScene::PostRender()
{
    naruto->PostRender();
    RobotManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
    skyBox->GUIRender();
}
