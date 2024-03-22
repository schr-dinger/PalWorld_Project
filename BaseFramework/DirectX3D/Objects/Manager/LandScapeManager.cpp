#include "Framework.h"

LandScapeManager::LandScapeManager()
{
    terrainF = new Terrain();
    terrain = new QuadTreeTerrain(L"Textures/HeightMaps/AWallTerrainH3.png");


    trees.reserve(treeN * treeN * 2);
    trees.reserve(treeN * treeN);

    //tree1 = new ModelInstancing("Tree1");
    //PlaceTree(tree1, treeN,terrainF,0);

    tree2 = new ModelInstancing("Tree2");
    PlaceTree(tree2, treeN,terrainF,0);

    rocks.reserve(rockN * rockN);

    rock1 = new ModelInstancing("Rock1");
    PlaceRock(rock1, rockN, terrainF);

    grasses.reserve(grassN1 * grassN1 + grassN2 * grassN2);

    grass1 = new ModelInstancing("Grass1");
    PlaceGrass(grass1, grassN1, terrainF);

    grass2 = new ModelInstancing("Grass2");
    PlaceGrass(grass2, grassN2, terrainF);

    shadow = new Shadow();
    
    //walls[0] = new CapsuleCollider(5.0f,26.0f);
    //walls[0]->Pos() = { 42.3,32.6,332.1 };
    //walls[0]->Rot() = { 0,1.0f * (XM_2PI / 360.0f),90.0f * (XM_2PI / 360.0f) };

    //walls[1] = new CapsuleCollider(15.0f, 50.0f);
    //walls[1]->Pos() = { 126.1f,31.6f,311.0f };
    //walls[1]->Rot() = { 0,22.0f * (XM_2PI / 360.0f),99.9f * (XM_2PI / 360.0f) };


    //walls[2] = new CapsuleCollider(15.0f, 70.0f);
    //walls[2]->Pos() = { 192.9f,28.8f,272.4f };
    //walls[2]->Rot() = { 0,39.0f * (XM_2PI / 360.0f),81.0f * (XM_2PI / 360.0f) };

    //walls[0]->SetTag("wall0");
    //walls[1]->SetTag("wall1");
    //walls[2]->SetTag("wall2");


    MakeObstacle();

    //for (Collider* collider : boxes) collider->UpdateWorld();


    FOR(2)
    {
        blendState[i] = new BlendState();
        rasterizer[i] = new RasterizerState();
    }
    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
    rasterizer[1]->CullMode(D3D11_CULL_NONE);
}

LandScapeManager::~LandScapeManager()
{
    for (Tree* tree : trees)    delete tree;


    for (Rock* rock : rocks)    delete rock;


    for (Grass* grass : grasses)delete grass;

    //delete tree1;
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
    for (Tree* tree : trees)
    {
        if ((tree->GetTransform()->Pos() - PlayerManager::Get()->GetPlayer()->Pos()).Length() < 50.0f && !tree->isDead)
        {
            tree->GetTransform()->SetActive(true);
        }
        else
        {
            tree->GetTransform()->SetActive(false);

        }
    }

    for (Grass* tree : grasses)
    {
        if ((tree->GetTransform()->Pos() - PlayerManager::Get()->GetPlayer()->Pos()).Length() > 150.0f)
        {
            tree->GetTransform()->SetActive(false);
        }
        else
        {
            tree->GetTransform()->SetActive(true);

        }
    }

    //tree1->Update();
    tree2->Update();
    rock1->Update();
    grass1->Update();
    grass2->Update();

    //FOR(3)
    //{
    //    walls[i]->UpdateWorld();
    //}


    for (Tree* tree : trees) tree->Update();
    for (Rock* rock : rocks) rock->Update();
    for (Grass* grass : grasses) grass->Update();

}

void LandScapeManager::PreRender()
{
}

void LandScapeManager::Render()
{
    //PreRender();

    //shadow->SetRender();
    //tree1->SetShader(L"Light/Shadow.hlsl");
    terrain->GetMaterial()->SetShader(L"Light/Shadow.hlsl");

    //blendState[1]->SetState();
    rasterizer[1]->SetState();
    //tree1->Render();
    tree2->Render();
    blendState[0]->SetState();
    rasterizer[0]->SetState();

    rock1->Render();
    grass1->Render();
    grass2->Render();

    terrain->Render();

    for (Tree* tree : trees) tree->Render();
    for (Rock* rock : rocks) rock->Render();
    for (Grass* grass : grasses) grass->Render();
    //for (Collider* collider : boxes) collider->Render();

    FOR(3)
    {
        //walls[i]->Render();
    }

}

void LandScapeManager::GUIRender()
{
    //FOR(3)
    //{
    //    walls[i]->GUIRender();
    //}

    for (Tree* tree : trees)
    {
        tree->GUIRender();
    }
}

void LandScapeManager::PlaceTree(ModelInstancing* tree, int size, Terrain* terrain, bool one)
{
    for (float z = 0; z < size; ++z)
    {
        for (float x = 1; x <= size; ++x)
        {
            Transform* transform = tree->Add();
            transform->Rot().x += XM_PIDIV2;
            transform->Rot().y = RANDOM->Float(0.0f, XM_2PI);

            transform->Pos() = { x * (WIDTH / size) + Random(-50.0f,50.0f) ,0, z * (WIDTH / size) + Random(-50.0f,50.0f) };
            transform->Pos().y = -30.0f;
            transform->Scale() *= 0.01f;

            if (terrain->GetHeight(transform->Pos()) < 20.0f)
            {
                transform->Pos().y = terrain->GetHeight(transform->Pos());
                Tree* tree = new Tree(transform, one);
                trees.push_back(tree);

            }
            else
            {
                transform->SetActive(false);
            }

            //Tree* tree = new Tree(transform,one);
            //trees.push_back(tree);
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
            transform->Rot().y = RANDOM->Float(0.0f,XM_2PI);

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
                //transform->Scale().z *= 5.0f;
                transform->Scale().z *= 3.0f;

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

bool LandScapeManager::CheckPalCollision(Collider* collider,Vector3& pos)
{
    for (Collider* obstacle : obstacles)
    {
        if (obstacle->IsCollision(collider))
        {
            pos = obstacle->GlobalPos();
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

    //FOR(3)
    //{
    //    obstacles.push_back(walls[i]);
    //}


    //for (int x = 0; x < 250; x++)
    //{
    //    for (int z = 0; z < 250; z++)
    //    {
    //        Vector3 tmpNormal;
    //        float h = terrainF->GetHeight({ (float)x,0,(float)z }, &tmpNormal);
    //        Vector3 normalG = -tmpNormal.GetNormalized();
    //        Vector3 up = { 0,1,0 };
    //        float k = Dot(up, normalG);

    //        if (k < 0.9f)
    //        {
    //            BoxCollider* cube = new BoxCollider();
    //            cube->Pos() = { (float)x,h,(float)z };
    //            boxes.push_back(cube);
    //            obstacles.push_back(cube);
    //        }
    //    }
    //}

    //for (int x = 5; x < 495; x++)
    //{
    //    for (int z = 5; z < 495; z++)
    //    {
    //        float i = terrainF->GetHeight({ (float)x,0,(float)z });
    //        float j = terrainF->GetHeight({ (float)(x+0),0,(float)(z+1) });
    //        float k = terrainF->GetHeight({ (float)(x + 1),0,(float)(z + 0) });
    //        float l = terrainF->GetHeight({ (float)(x - 1),0,(float)(z + 0) });
    //        float m = terrainF->GetHeight({ (float)(x + 0),0,(float)(z - 1) });

    //        float d = 0.9f;

    //        if (i - j > d)
    //        {
    //            BoxCollider* cube = new BoxCollider();
    //            cube->Pos() = { (float)(x+0),i,(float)(z+1) };
    //            boxes.push_back(cube);
    //            //obstacles.push_back(cube);
    //        }

    //        if (i - k > d)
    //        {
    //            BoxCollider* cube = new BoxCollider();
    //            cube->Pos() = { (float)(x + 1),i,(float)(z + 0) };
    //            boxes.push_back(cube);
    //            //obstacles.push_back(cube);
    //        }

    //        if (i - l > d)
    //        {
    //            BoxCollider* cube = new BoxCollider();
    //            cube->Pos() = { (float)(x - 1),i,(float)(z + 0) };
    //            boxes.push_back(cube);
    //            //obstacles.push_back(cube);
    //        }

    //        if (i - m > d)
    //        {
    //            BoxCollider* cube = new BoxCollider();
    //            cube->Pos() = { (float)(x + 0),i,(float)(z - 1) };
    //            boxes.push_back(cube);
    //            //obstacles.push_back(cube);
    //        }

    //        //if (abs(i - j) > 0.75f && abs(i - k) > 0.75f)
    //        //{
    //        //    BoxCollider* cube = new BoxCollider();
    //        //    cube->Pos() = { (float)x,i,(float)z };
    //        //    boxes.push_back(cube);
    //        //    //obstacles.push_back(cube);

    //        //}
    //    }
    //}

}
