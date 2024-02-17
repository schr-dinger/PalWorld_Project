#pragma once
class WaterScene : public Scene
{
public:
    WaterScene();
    ~WaterScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    SkyBox* skyBox;
    Model* forest; // �� ���
    Human* human;  // �׽�Ʈ�� �ΰ� ��

    //�� ���� ���ΰ�
    Water* water;
};

