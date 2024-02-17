#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
    skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    forest = new Model("Forest");
    forest->Pos() += { 0, -10, 0 }; //배경 위치 조정(필수 아님)

    human = new Human();

    water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
}

WaterScene::~WaterScene()
{
    delete skyBox;
    delete forest;
    delete human;
    delete water;
}

void WaterScene::Update()
{
    human->Update();
    forest->UpdateWorld();
    water->Update();
}

void WaterScene::PreRender()
{
    // 렌더 타겟 연산 진행과 그 결과를 출력하기

    //일렁임
    water->SetRefraction();

    //일렁임 쪽 클래스의 쿼드에 일렁임의 결과 출력
    skyBox->Render();
    forest->Render();
    human->Render();

    //반사
    water->SetReflection();

    //반사 출력
    skyBox->Render();
    forest->Render();
    human->Render();
}

void WaterScene::Render()
{
    skyBox->Render();
    forest->Render();
    water->Render();
    human->Render();
}

void WaterScene::PostRender()
{
}

void WaterScene::GUIRender()
{
    water->GUIRender();
}
