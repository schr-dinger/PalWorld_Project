#pragma once
class LandScapeManager : public Singleton<LandScapeManager>
{
public:
    LandScapeManager();
    ~LandScapeManager();

    void Update();
    void Render();
    void GUIRender();

    void PlaceTree(ModelInstancing* tree,int size,Terrain* terrain);
    void PlaceRock(ModelInstancing* tree, int size, Terrain* terrain);


    Terrain* GetTerrain() { return terrainF; }
private:

private:
    Terrain* terrainF;


    ModelInstancing* tree1;
    ModelInstancing* tree2;
    ModelInstancing* rock1;

    vector<Tree*> trees;
    //vector<Tree*> trees2;
    vector<Rock*> rocks;

    //ModelInstancing* tree3;




    int treeN = 5;

    int rockN = 3;


    float WIDTH = 500;
    float HEIGHT = 500;

    bool isPlaced1 = false;
    bool isPlaced2 = false;
    bool isPlaced3 = false;

};

