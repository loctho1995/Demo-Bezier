#include "SceneManager.h"

SceneManager* SceneManager::mInstace = NULL;
Scene*  SceneManager::mCurrentScene = NULL;

SceneManager::SceneManager()
{
    mCurrentScene = nullptr;
}


SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
    if (!mInstace)
        mInstace = new SceneManager();

    return mInstace;
}

Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

void SceneManager::ReplaceScene(Scene *scene)
{
    mCurrentScene = scene;
}
