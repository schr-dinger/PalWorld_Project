#include "Framework.h"

Grass::Grass(Terrain* terrain) : terrain(terrain)
{
    grass1 = new ModelInstancing("Grass1");
    Place(grass1);


    grass2 = new ModelInstancing("Grass2");
    Place(grass2);
}

Grass::~Grass()
{
    delete grass1;
    delete grass2;
}

void Grass::Update()
{
    grass1->Update();
    grass2->Update();
}

void Grass::Render()
{
    grass1->Render();
    grass2->Render();
}

void Grass::GUIRender()
{
}

void Grass::Place(ModelInstancing* grass)
{
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 1; x <= SIZE; ++x)
        {
            Transform* transform = grass->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = x;
            //transform->Pos() = { x*SIZE/WIDTH, terrain->GetHeight(transform->Pos()), z*SIZE/HEIGHT };
            transform->Pos() = { x * (WIDTH / SIZE) + Random(-50.0f,50.0f) , 0, z * (WIDTH / SIZE) + Random(-50.0f,50.0f) };
            if (terrain->GetHeight(transform->Pos()) < 20.0f)
            {
                transform->Pos().y = terrain->GetHeight(transform->Pos());
            }

            transform->Scale() *= 0.01f;
            if (grass == grass2)
            {
                transform->Scale().x *= 5.0f;
                transform->Scale().z *= 5.0f;
            }
        }
    }
}
