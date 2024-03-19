#pragma once

class ModelInstancing : public Model
{
public:
    ModelInstancing(string name);
    ~ModelInstancing();

    void Update();
    void Render();
    void GUIRender();

    Transform* Add();

    vector<Transform*>& GetTransforms() { return transforms; }

private:
    vector<Transform*> transforms;
    InstanceData instanceDatas[MAX_INSTANCE];

    VertexBuffer* instanceBuffer;

    UINT drawCount = 0;
};