#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
    //modelAnimator = new ModelAnimator("Human"); // �𵨸����� �ִϸ����� ����
    //modelAnimator->ReadClip("Idle", 1);         // ������ �����ƴ� Ŭ�������� ������ �ҷ�����
    //modelAnimator->ReadClip("Run", 1);          // ������ �̸��� .fbx�� ����Ǿ��� �����̸�(Ŭ����)���� ���� ��
    //modelAnimator->ReadClip("Jump", 1);         // fbx ��� ���α׷� ���� ����ϸ� Ŭ����, ��Ÿ ���� Ȯ�� ����
    //                                            // ���� ��� ���α׷��� ����, ���� ���α׷��� �����ϴ� (�� : 3Ds MAX)

    // ������ ���ۿ� ���� ReadClip �Լ� ����
    // : ���� ������ ���� Ŭ���� �Һз��� ������ ���, ȣ���� �� Ŭ���� ��(Ȥ�� ����)�� �Ű������� �ϳ� �� �ָ� OK
    //   -> ���� �ִ� ȣ�� (Ŭ���� + Ŭ����) , �Ʒ����� �׷� ������ ��� Ŭ�������ε� ȣ�Ⱑ��

    // ���� �ִϸ����� ������ ���� : �ؽ�ó�� �׷����ĵ�, ���� ������, ���� ����, ������ ��������
    // ��� ��¿� ������ ���� �����͸� ������ ���Ͽ��� ���� �� ������ �����ؼ� ����Ѵٴ� ��
    
    // -> ��ü�� �������� ���� �� ��ü�� ���� ����ŭ ��ǻ�Ͱ� �δ��� ���Ȱ� �ȴ�

    // -> �ذ� ��� : �� ���� �� ������ ĳ���Ͱ� ���� ���� ��, �ش� ĳ���͸� �����ϴ� �������� ���
    //    (����, � ������ �ִ���, � ���븦 ��������...) ���� �� ������ �����ϰ�,
    //    ������� ���� ��ü�� �ش� ��ü���� ������ ���� ������ (Ʈ������ ������, ���� ������ �� ��)
    //    �ٸ� ��ü�� ���� ������ ���� ������(�����, �ؽ�ó, ����, ����) �ϳ��� ���ļ� �����ϴ� ��
    //    �׷��� ������ �ʿ��� ��ǻ���� ������ ����� ���� �� �ְ� �ȴ�

    // = ��, Ȥ�� �ִϸ��̼��� ���� �� ������ (Animation Instancing, �ִϸ��̼� �ν��Ͻ�)

    // * ���� �����ϸ� ���� ��� 

    // 1. ��ο� ���� : ��ü �ϳ��� �׸��� ���� �ʿ��� ������ ����. ����, ����, ����ġ, ��Ƽ���� ���� ��Ī
    // 2. ��ο� �� : ��ǻ�Ͱ� �����ð��� ��ο� ������ ���� ��. �̰� �ʹ� ������ ��ǻ���� ����� �������� (���� ��������)

    // -> �ִϸ��̼� �ν��Ͻ��� �ٸ��� ǥ���ϸ�, ��ο� ������ ��������, ��ο� ���� ���̴� ���

    // : �ڼ��� �ڵ�� �� �ν��Ͻ�->�ִϸ��̼� �ν��Ͻ̿���

    //modelAnimator = new ModelAnimator("Fox");
    //modelAnimator->ReadClip("Fox_Run");



    modelAnimator = new ModelAnimator("NPC");
    
    modelAnimator->ReadClip("work",0);
    modelAnimator->ReadClip("work", 1);

    testyo = new Transform();
    test = new Model("PickExe");
       
    test->SetParent(testyo);
    modelAnimator->Scale() *= 0.01f;

    //modelAnimator = new ModelAnimator("PenGuin");
    //modelAnimator->ReadClip("Idle");
    //modelAnimator->ReadClip("Walk");
    //modelAnimator->ReadClip("Run");
    //modelAnimator->ReadClip("Attack");
    //modelAnimator->ReadClip("Damage");
    //modelAnimator->ReadClip("Work");

    // modelAnimator2 = new ModelAnimator("PenGuin");
    // modelAnimator2->ReadClip("Idle");
    // modelAnimator2->ReadClip("Walk");
    // modelAnimator2->ReadClip("Run");
    // modelAnimator2->ReadClip("Attack");
    // modelAnimator2->ReadClip("Damage");
    // modelAnimator2->ReadClip("Work");
    // modelAnimator2->SetTag("2");
    // modelAnimator2->SetShader(L"Basic/Texture.hlsl");
    // 
    // FOR(2) blendState[i] = new BlendState();
    // 
    // blendState[1]->Alpha(true);
    // blendState[1]->AlphaToCoverage(true);
}

ModelAnimationScene::~ModelAnimationScene()
{
    delete modelAnimator;
    delete modelAnimator2;
}

void ModelAnimationScene::Update()
{
    if (KEY_DOWN('1'))
        modelAnimator->PlayClip(0);
    if (KEY_DOWN('2'))
        modelAnimator->PlayClip(1);
    if (KEY_DOWN('3'))
        modelAnimator->PlayClip(2);
    if (KEY_DOWN('4'))
        modelAnimator->PlayClip(3);
    if (KEY_DOWN('5'))
        modelAnimator->PlayClip(4);
    testyo->SetWorld(modelAnimator->GetTransformByNode(68));

    
    modelAnimator->Update();
    test->UpdateWorld();
    //modelAnimator2->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
    //blendState[1]->SetState();
    modelAnimator->Render();
    //modelAnimator2->Render();
    //blendState[0]->SetState();
    test->Render();

}

void ModelAnimationScene::PostRender()
{
}

void ModelAnimationScene::GUIRender()
{
    //modelAnimator->GUIRender();
    //modelAnimator2->GUIRender();

    test->GUIRender();
}

void ModelAnimationScene::SetIdle()
{
    modelAnimator->PlayClip(0, 1.0f, 0.1f);
}
