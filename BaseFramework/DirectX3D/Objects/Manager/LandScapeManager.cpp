#include "Framework.h"

LandScapeManager::LandScapeManager()
{
    terrainF = new Terrain();
    terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");


    trees.reserve(treeN * treeN * 2);

    tree1 = new ModelInstancing("Tree1");
    PlaceTree(tree1, treeN,terrainF);

    tree2 = new ModelInstancing("Tree2");
    PlaceTree(tree2, treeN,terrainF);

    rocks.reserve(rockN * rockN);

    rock1 = new ModelInstancing("Rock1");
    PlaceRock(rock1, rockN, terrainF);

    grasses.reserve(grassN1 * grassN1 + grassN2 * grassN2);

    grass1 = new ModelInstancing("Grass1");
    PlaceGrass(grass1, grassN1, terrainF);

    grass2 = new ModelInstancing("Grass2");
    PlaceGrass(grass2, grassN2, terrainF);

    shadow = new Shadow();

    MakeObstacle();
}

LandScapeManager::~LandScapeManager()
{
    for (Tree* tree : trees)    delete tree;


    for (Rock* rock : rocks)    delete rock;


    for (Grass* grass : grasses)delete grass;

    delete tree1;
    delete tree2;
    delete rock1;
    delete grass1;
    delete grass2;

    delete shadow;

    delete terrainF;
    delete terrain;

}

void LandScapeManager::Update()
{
    tree1->Update();
    tree2->Update();
    rock1->Update();
    grass1->Update();
    grass2->Update();


    for (Tree* tree : trees) tree->Update();
    for (Rock* rock : rocks) rock->Update();
    for (Grass* grass : grasses) grass->Update();

}

void LandScapeManager::PreRender()
{
    shadow->SetRenderTarget();
    tree1->SetShader(L"Light/DepthMap.hlsl");

    //tree2->SetShader(L"Light/DepthMap.hlsl");

    //rock1->SetShader(L"Light/DepthMap.hlsl");

    //grass1->SetShader(L"Light/DepthMap.hlsl");

    //grass2->SetShader(L"Light/DepthMap.hlsl");

    tree1->Render();
    //tree2->Render();
    //rock1->Render();
    //grass1->Render();
    //grass2->Render();
}

void LandScapeManager::Render()
{
    //PreRender();

    //shadow->SetRender();
    //tree1->SetShader(L"Light/Shadow.hlsl");
    //terrain->GetMaterial()->SetShader(L"Light/Shadow.hlsl");


    tree1->Render();
    tree2->Render();
    rock1->Render();
    grass1->Render();
    grass2->Render();

    terrain->Render();

    for (Tree* tree : trees) tree->Render();
    for (Rock* rock : rocks) rock->Render();
    for (Grass* grass : grasses) grass->Render();

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

void LandScapeManager::PlaceGrass(ModelInstancing* tree, int size, Terrain* terrain)
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

            if (tree == grass2)
            {
                transform->Scale().x *= 5.0f;
                transform->Scale().y *= 5.0f;
                transform->Scale().z *= 5.0f;
            }
            else
            {
                transform->Scale().z *= 3.0f;
            }

            if (terrain->GetHeight(transform->Pos()) < 20.0f)
            {
                transform->Pos().y = terrain->GetHeight(transform->Pos());
            }
            else
            {
                transform->SetActive(false);
            }

            Grass* grass = new Grass(transform);
            grasses.push_back(grass);
        }
    }

}

bool LandScapeManager::CheckPalCollision(Collider* collider)
{
    for (Collider* obstacle : obstacles)
    {
        if (obstacle->IsCollision(collider))
        {
            return true;
        }
    }

    return false;

}

void LandScapeManager::MakeObstacle()
{
    for (Tree* tree : trees)
    {
        if (tree->GetTransform()->Active())
        {
            obstacles.push_back(tree->GetCollider());
        }
    }

    for (Rock* rock : rocks)
    {
        if (rock->GetTransform()->Active())
        {
            obstacles.push_back(rock->GetCollider());
        }

    }


}
