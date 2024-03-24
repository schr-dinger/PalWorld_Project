#pragma once

class DepthStencilState
{
public:
    DepthStencilState();
    ~DepthStencilState();

    void SetState();

    void DepthEnable(bool value);
    void DepthWriteMask(D3D11_DEPTH_WRITE_MASK value);
    void DepthFunc(D3D11_COMPARISON_FUNC value);
    void StencilEnable(bool value);

    void Changed();

private:
    D3D11_DEPTH_STENCIL_DESC desc = {};
    ID3D11DepthStencilState* state = nullptr;
};