#pragma once
class LandScapeManager : public Singleton<LandScapeManager>
{
public:
    LandScapeManager();
    ~LandScapeManager();

    void Update();
    void PreRender();
    void Render();
    void GUIRender();

    void PlaceTree(ModelInstancing* tree,int size,Terrain* terrain,bool one);
    void PlaceRock(ModelInstancing* tree, int size, Terrain* terrain);
    void PlaceGrass(ModelInstancing* tree, int size, Terrain* terrain);


    Terrain* GetTerrain() { return terrainF; }

    QuadTreeTerrain* terrain;

    vector<Collider*>& GetObstacles() { return obstacles; }

    bool CheckPalCollision(Collider* collider,Vector3& pos);

    //ModelInstancing* GetTree1Instancing() { return tree1; }
    ModelInstancing* GetTree2Instancing() { return tree2; }
    ModelInstancing* GetRock1Instancing() { return rock1; }
    ModelInstancing* GetGrass1Instancing() { return grass1; }
    ModelInstancing* GetGrass2Instancing() { return grass2; }

    vector<Tree*>& GetTrees() { return trees; }
    vector<Rock*>& GetRocks() { return rocks; }

private:
    void MakeObstacle();
private:
    Terrain* terrainF;

    //ModelInstancing* tree1;
    ModelInstancing* tree2;
    ModelInstancing* rock1;
    ModelInstancing* grass1;
    ModelInstancing* grass2;


    vector<Tree*> trees;
    vector<Rock*> rocks;
    vector<Grass*> grasses;

    vector<Collider*> obstacles;

    //vector<Collider*> boxes;

    //CapsuleCollider* walls[3];

    Shadow* shadow;

    //int treeN = 10;
    int treeN = 12;

    int rockN = 10;

    int grassN1 = 2;

    //int grassN2 = 20;
    int grassN2 = 20;

    float WIDTH = 500;
    float HEIGHT = 500;

    bool isPlaced1 = false;
    bool isPlaced2 = false;
    bool isPlaced3 = false;

    BlendState* blendState[2];
    RasterizerState* rasterizer[2];

};

