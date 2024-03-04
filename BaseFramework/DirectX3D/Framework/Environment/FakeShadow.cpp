#include "Framework.h"
#include "FakeShadow.h"

FakeShadow::FakeShadow(UINT width, UINT height)
    : width(width), height(height)
{
    renderTarget = new RenderTarget(width, height);
    depthStencil = new DepthStencil(width, height);
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();
}

FakeShadow::~FakeShadow()
{
    delete renderTarget;
    delete depthStencil;
    delete viewBuffer;
    delete projectionBuffer;
}

void FakeShadow::SetRenderTarget(int n)
{
    renderTarget->Set(depthStencil);
    //renderTarget->Set(depthStencil, {1.0f,0.5f,0.0f,1.0f}); // 렌더 타겟 설정 (테스트씬에서는 프리렌더에서 했던 것)

    SetViewProjection(n);
}

void FakeShadow::SetRender()
{
    viewBuffer->SetVS(11);
    projectionBuffer->SetVS(12);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
}

void FakeShadow::PostRender()
{
}

void FakeShadow::GUIRender()
{
    ImGui::SliderFloat("Scale", &scale, 1, 10);
}

void FakeShadow::SetViewProjection(int n)
{
    LightBuffer::Light* light = Environment::Get()->GetLight(n);
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 1000);
    viewBuffer->Set(view, XMMatrixInverse(nullptr, view));                                                          
    projectionBuffer->Set(projection);
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
