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

    void PlaceTree(ModelInstancing* tree,int size,Terrain* terrain);
    void PlaceRock(ModelInstancing* tree, int size, Terrain* terrain);
    void PlaceGrass(ModelInstancing* tree, int size, Terrain* terrain);


    Terrain* GetTerrain() { return terrainF; }

    QuadTreeTerrain* terrain;

private:

private:
    Terrain* terrainF;

    ModelInstancing* tree1;
    ModelInstancing* tree2;
    ModelInstancing* rock1;
    ModelInstancing* grass1;
    ModelInstancing* grass2;


    vector<Tree*> trees;
    vector<Rock*> rocks;
    vector<Grass*> grasses;

    Shadow* shadow;

    int treeN = 5;

    int rockN = 3;

    int grassN = 6;

    float WIDTH = 500;
    float HEIGHT = 500;

    bool isPlaced1 = false;
    bool isPlaced2 = false;
    bool isPlaced3 = false;

};

