#include "Framework.h"

Rock::Rock(Terrain* terrain) : terrain(terrain)
{
	rock1 = new ModelInstancing("Rock1");
	Place(rock1);

}

Rock::~Rock()
{
	delete rock1;
}

void Rock::Update()
{
	rock1->Update();
}

void Rock::Render()
{
	rock1->Render();
}

void Rock::GUIRender()
{
}

void Rock::Place(ModelInstancing* tree)
{
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 1; x <= SIZE; ++x)
        {
            Transform* transform = tree->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = x;
            //transform->Pos() = { x*SIZE/WIDTH, terrain->GetHeight(transform->Pos()), z*SIZE/HEIGHT };
            transform->Pos() = { x * (WIDTH / SIZE) + Random(-50.0f,50.0f) ,0, z * (WIDTH / SIZE) + Random(-50.0f,50.0f) };
            transform->Pos().y = terrain->GetHeight(transform->Pos());
            //if (terrain->GetHeight(transform->Pos()) < 20.0f)
            //{
            //    transform->Pos().y = terrain->GetHeight(transform->Pos());
            //}


            transform->Scale() *= 0.01f;
        }
    }
}
