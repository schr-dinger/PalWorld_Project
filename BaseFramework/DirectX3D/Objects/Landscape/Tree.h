#pragma once
class Tree
{
public:
    Tree(Terrain* terrain);
    ~Tree();

    void Update();
    void Render();
    void GUIRender();

private:
    void Place(ModelInstancing* tree);
private:
    ModelInstancing* tree1;
    ModelInstancing* tree2;
    //ModelInstancing* tree3;


    Terrain* terrain;


    int SIZE = 5;
    float WIDTH = 500;
    float HEIGHT = 500;

};

