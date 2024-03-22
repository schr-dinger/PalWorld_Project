#include "Framework.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    //for (pair<string, Scene*> scene : scenes)
    for (auto scene : scenes)
        delete scene.second;
}

void SceneManager::Update()
{
    //for (Scene* scene : curScenes)
    //    scene->Update();
    if (changingTime > 0.0f)
    {
        changingTime -= DELTA;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            delete currentScene;
            nextScene->Start();
        }
    }


    if (isChanging)
    {
        currentScene = nextScene;
        isChanging = false;
    }
    currentScene->Update();


}

void SceneManager::PreRender()
{
    //for (Scene* scene : curScenes)
    //    scene->PreRender();
    if (isChanging)return;
    currentScene->PreRender();

}

void SceneManager::Render()
{
    //for (Scene* scene : curScenes)
    //    scene->Render();
    if (isChanging)return;
    currentScene->Render();

}

void SceneManager::PostRender()
{
    //for (Scene* scene : curScenes)
    //    scene->PostRender();
    if (isChanging)return;
    currentScene->PostRender();

}

void SceneManager::GUIRender()
{
    //for (Scene* scene : curScenes)
    //    scene->GUIRender();
    if (isChanging)return;
    currentScene->GUIRender();

}

void SceneManager::Create(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return;

    scenes[key] = scene;
}

Scene* SceneManager::Add(string key)
{
    if (scenes.count(key) == 0)
        return nullptr;

    list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[key]);

    if (findScene != curScenes.end())
        return  scenes[key];

    curScenes.push_back(scenes[key]);
    curScenes.back()->Start();

    return scenes[key];
}

void SceneManager::Remove(string key)
{
    if (scenes.count(key) == 0)
        return;

    list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[key]);

    if (findScene == curScenes.end())
        return;

    scenes[key]->End();
    curScenes.erase(findScene);
}

Scene* SceneManager::GetScene(string key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return nullptr;
    }

    return iter->second;
}

Scene* SceneManager::ChangeScene(string key, float changingTime)
{
    Scene* temp = GetScene(key);

    if (temp)
    {
        nextScene = temp;
        this->changingTime = changingTime;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            delete currentScene;
            nextScene->Start();
        }
    }
    return temp;
}
