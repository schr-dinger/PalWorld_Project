#pragma once
class FakeShadow
{
public:
    FakeShadow(UINT width = 2000, UINT height = 2000);
    ~FakeShadow();

    void SetRenderTarget(int n);
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection(int n);

private:
    float scale = 100;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    UINT width;
    UINT height;
};

