#include "Framework.h"

LandScapeManager::LandScapeManager()
{
    terrainF = new Terrain();

    trees.reserve(treeN * treeN * 2);

    tree1 = new ModelInstancing("Tree1");
    PlaceTree(tree1, treeN,terrainF);

    tree2 = new ModelInstancing("Tree2");
    PlaceTree(tree2, treeN,terrainF);

    rocks.reserve(rockN * rockN);

    rock1 = new ModelInstancing("Rock1");
    PlaceRock(rock1, rockN, terrainF);


}

LandScapeManager::~LandScapeManager()
{
    for (Tree* tree : trees)
        delete tree;

    for (Rock* rock : rocks)
        delete rock;

    delete tree1;
    delete tree2;
    delete rock1;

    delete terrainF;
}

void LandScapeManager::Update()
{

    tree1->Update();
    tree2->Update();
    rock1->Update();

    for (Tree* tree : trees) tree->Update();
    for (Rock* rock : rocks) rock->Update();
}

void LandScapeManager::Render()
{
    tree1->Render();
    tree2->Render();
    rock1->Render();

    for (Tree* tree : trees) tree->Render();
    for (Rock* rock : rocks) rock->Render();
}

void LandScapeManager::GUIRender()
{
}

void LandScapeManager::PlaceTree(ModelInstancing* tree, int size, Terrain* terrain)
{
    for (float z = 0; z < size; ++z)
    {
        for (float x = 1; x <= size; ++x)
        {
            Transform* transform = tree->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = x;

            transform->Pos() = { x * (WIDTH / size) + Random(-50.0f,50.0f) ,0, z * (WIDTH / size) + Random(-50.0f,50.0f) };
            transform->Pos().y = -30.0f;
            transform->Scale() *= 0.01f;

            if (terrain->GetHeight(transform->Pos()) < 20.0f)
            {
                transform->Pos().y = terrain->GetHeight(transform->Pos());
            }
            else
            {
                transform->SetActive(false);
            }

            Tree* tree = new Tree(transform);
            trees.push_back(tree);
        }
    }

}

void LandScapeManager::PlaceRock(ModelInstancing* tree, int size, Terrain* terrain)
{
    for (float z = 0; z < size; ++z)
    {
        for (float x = 1; x <= size; ++x)
        {
            Transform* transform = tree->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = x;

            transform->Pos() = { x * (WIDTH / size) + Random(-50.0f,50.0f) ,0, z * (WIDTH / size) + Random(-50.0f,50.0f) };
            transform->Pos().y = -30.0f;
            transform->Scale() *= 0.01f;

            transform->Pos().y = terrain->GetHeight(transform->Pos());

            Rock* rock = new Rock(transform);
            rocks.push_back(rock);
        }
    }

}
