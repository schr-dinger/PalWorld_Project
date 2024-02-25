#include "Framework.h"

Tree::Tree(Terrain* terrain) : terrain(terrain)
{
	tree1 = new ModelInstancing("Tree1");
    Place(tree1);

    //tree2 = new ModelInstancing("Tree2");
    //Place(tree2);
}

Tree::~Tree()
{
	delete tree1;
}

void Tree::Update()
{
	tree1->Update();
}

void Tree::Render()
{
	tree1->Render();
}

void Tree::GUIRender()
{
}

void Tree::Place(ModelInstancing* tree)
{
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 1; x <= SIZE; ++x)
        {
            Transform* transform = tree->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = x;
            //transform->Pos() = { x*SIZE/WIDTH, terrain->GetHeight(transform->Pos()), z*SIZE/HEIGHT };
            transform->Pos() = { x*(WIDTH/SIZE) + Random(-50.0f,50.0f) , terrain->GetHeight({x,0,z}), z* (WIDTH / SIZE) + Random(-50.0f,50.0f) };
            transform->Pos().y = terrain->GetHeight(transform->Pos());

            transform->Scale() *= 0.01f;
        }
    }


}
