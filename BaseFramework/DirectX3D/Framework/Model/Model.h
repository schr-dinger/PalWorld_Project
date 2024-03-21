#pragma once

class Model : public Transform
{
public:
    string ModelName;

public:
    Model(string name);
    ~Model();

    void Render();
    void GUIRender();

    void SetShader(wstring file);

    Material* GetMaterial(int num) { return materials[num]; }
    vector<Material*>& GetMaterials() { return materials; }


private:
    void ReadMaterial();
    void ReadMesh();

protected:
    string name;

    vector<Material*> materials;
    vector<ModelMesh*> meshes;
    vector<NodeData> nodes;
    vector<BoneData> bones;

    map<string, UINT> boneMap;

    WorldBuffer* worldBuffer;
};