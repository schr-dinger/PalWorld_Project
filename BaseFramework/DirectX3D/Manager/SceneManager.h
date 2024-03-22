#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
    SceneManager();
    ~SceneManager();

    void Update();

    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void Create(string key, Scene* scene);

    Scene* Add(string key);
    void Remove(string key);
    Scene* GetScene(string key);

    Scene* ChangeScene(string key, float changingTime = 0.0f);


private:
    map<string, Scene*> scenes;

    list<Scene*> curScenes;

    bool    isChanging = false;
    Scene* nextScene = nullptr;
    Scene* currentScene = nullptr;

    float changingTime = 0.0f;
};