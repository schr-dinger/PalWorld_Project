#pragma once

class Terrain : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

    const float MIN_HEIGHT = 0.0f;
    const float MAX_HEIGHT = 70.0f;

    const UINT MAX_SIZE = 10000;

    class RayBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 pos;
            UINT triangleSize;

            Float3 dir;
            float padding;
        };

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

    struct InputDesc
    {
        Float3 v0, v1, v2;
    };

    struct OutputDesc
    {
        int picked;
        float distance;
    };

public:
    Terrain();
    Terrain(string mapFile);
    ~Terrain();

    void Render();

    float GetHeight(const Vector3& pos, Vector3* normal = nullptr);
    float GetHeightCompute(Vector3 pos);

    Vector3 Picking();
    bool ComputePicking(Vector3& pos);


    Vector2 GetSize() { return Vector2(width, height); } //가로 세로를 직접 받을 수 있게 추가

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();
    void MakeComputeData();

private:
    UINT width, height;
    UINT triangleSize;

    Vector3 pickingPos;

    Mesh<VertexType>* mesh;
    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer;
    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    Texture* heightMap;
    Texture* alphaMap;
    Texture* secondMap;
    Texture* thirdMap;

    ComputeShader* computeShader;

};