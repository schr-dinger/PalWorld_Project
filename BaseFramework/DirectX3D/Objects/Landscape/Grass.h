#pragma once
class Grass
{
public:
    Grass(Transform* transform);
    ~Grass();

    void Update();
    void Render();
    void GUIRender();

    Transform* GetTransform() { return transform; }
private:

    Transform* transform;

};

