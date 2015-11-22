#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "GameLog.h"
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager *GetInstance();
    ~SceneManager();

    Scene* GetCurrentScene();
    void ReplaceScene(Scene *scene);

private:
    SceneManager();
    static SceneManager     *mInstace;
    static Scene            *mCurrentScene;
};

#endif