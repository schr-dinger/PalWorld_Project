#pragma once
class Rock
{
public:
    Rock(Terrain* terrain);
    ~Rock();

    void Update();
    void Render();
    void GUIRender();

private:
    void Place(ModelInstancing* rock);
private:
    ModelInstancing* rock1;
    //ModelInstancing* tree2;
    //ModelInstancing* tree3;


    Terrain* terrain;


    int SIZE = 4;
    float WIDTH = 500;
    float HEIGHT = 500;

};

