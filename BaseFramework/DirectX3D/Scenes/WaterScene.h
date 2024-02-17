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
    Model* forest; // 숲 배경
    Human* human;  // 테스트용 인간 모델

    //이 씬의 주인공
    Water* water;
};

