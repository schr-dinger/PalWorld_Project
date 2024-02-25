#pragma once
class Grass
{
public:
    Grass(Terrain* terrain);
    ~Grass();

    void Update();
    void Render();
    void GUIRender();

private:
    void Place(ModelInstancing* grass);
private:
    ModelInstancing* grass1;
    ModelInstancing* grass2;
    //ModelInstancing* tree3;


    Terrain* terrain;


    int SIZE = 10;
    float WIDTH = 500;
    float HEIGHT = 500;

};

