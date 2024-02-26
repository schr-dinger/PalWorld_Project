#pragma once

class QuadTreeTerrain : public GameObject
{
    // ���� Ʈ�� �ͷ��� : ����Ʈ�� �ڷ� ������ ������ �ͷ��� Ŭ����

private:
    float MAX_HEIGHT = 70;
    //UINT MIN_TRIANGLE = 2048; // �ڷ� ������ ���� ��, �� ������ �����ϱ� ���� �ּ� �ﰢ ����
    UINT MIN_TRIANGLE = 120480;                          // �� ���ڸ� �� ä��� ������ �ɰ����� �ʵ��� �� ��
    //UINT MIN_TRIANGLE = 200000; //�̰Ÿ� 4����

    // * �� �ּ� �ﰢ�� �ܿ��� Ʈ���� �ɰ��� ������ �����ڰ� �ʿ信 ���� ������ �� �ִ�

    typedef VertexUVNormal VertexType;

    struct Node // ������ ����Ʈ���� ���� ������ ���Ҵ���
                // ...A*�� ���̴� �Ͱ��� �ٸ���
    {
        //���Ҵ������� �ʿ��� ������

        float x, z, size; // ����� ��ġ, ����� ũ��
        UINT triangleCount; //�� ��尡 ���� �ִ� �ﰢ��(=������ ���)�� ����

        Mesh<VertexType>* mesh = nullptr;
                        //�� ������ ���� �ִ�(��ü ������ �κ�����) ����

        Node* children[4] = {}; //Ʈ�� ���� = �θ� �ؿ� ������ Ÿ���� �ڽĵ��� ����
                                // �ڽ��� ���̶� ���� Ʈ��
    };

public:
    QuadTreeTerrain(wstring heightFile);
    ~QuadTreeTerrain();

    void Render();
    void GUIRender();

private:
    void RenderNode(Node* node); //������ ����� ���� ����
    void DeleteNode(Node* node);

    // �޽��� ��ġ ���
    void CalcMeshDimension(UINT vertexCount,
        float& centerX, float& centerZ, float& size);

    //�Ű������� ���õ� ���� �ﰢ���� �ִ°�?
    bool IsTriangleContained(UINT index, float x, float z, float size);
    //�׷��� �ִٸ� �󸶳� �ִ°�?
    UINT ContainedTriangleCount(float x, float z, float size);

    //��� �����(����Ʈ�� �����)
    void CreateTreeNode(Node* node, float x, float z, float size);

private:
    UINT width;
    UINT height;
    UINT triangleCount = 0;
    UINT drawCount = 0;

    TerrainData* terrainData;
    vector<VertexType> vertices;

    Node* root;


};

