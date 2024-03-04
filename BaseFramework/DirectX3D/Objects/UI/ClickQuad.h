#pragma once
class ClickQuad
{
public:
    ClickQuad();
    ~ClickQuad();

    void Update();
    void Render();
    void PostRender();
    void GuiRender();

    bool MouseCollision();

    Quad* GetQuad() { return click; }

private:

protected:
    Quad* click;
};

