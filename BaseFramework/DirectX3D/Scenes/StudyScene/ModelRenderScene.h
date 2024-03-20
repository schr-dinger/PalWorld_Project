#pragma once

class ModelRenderScene : public Scene
{
public:
    ModelRenderScene();
    ~ModelRenderScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Model* Spike[3];
};