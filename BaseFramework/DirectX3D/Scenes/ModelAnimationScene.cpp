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

    modelAnimator = new ModelAnimator("ElecP");
    modelAnimator->ReadClip("ElecP_run");
    modelAnimator->ReadClip("ElecP_skill");
    modelAnimator->ReadClip("ElecP_damage");

    //modelAnimator->ReadClip("test_encount");
    //modelAnimator->ReadClip("test_damage");
    //modelAnimator->ReadClip("test_attack");
    //modelAnimator->ReadClip("test_sleepL");
    //modelAnimator->ReadClip("test_sleepS");
    //modelAnimator->ReadClip("test_sleepE");

    
    modelAnimator->Scale() *= 0.01f;
    /*modelAnimator->ReadClip("Walk");
    modelAnimator->ReadClip("Dying");
    modelAnimator->ReadClip("StandUp");
    modelAnimator->ReadClip("Hit");*/
    modelAnimator->PlayClip(0);
}

ModelAnimationScene::~ModelAnimationScene()
{
    delete modelAnimator;
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



    modelAnimator->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
    modelAnimator->Render();
}

void ModelAnimationScene::PostRender()
{
}

void ModelAnimationScene::GUIRender()
{
    modelAnimator->GUIRender();
}

void ModelAnimationScene::SetIdle()
{
    modelAnimator->PlayClip(0, 1.0f, 0.1f);
}
