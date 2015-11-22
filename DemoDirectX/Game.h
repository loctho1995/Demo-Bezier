#ifndef __GAME__
#define __GAME__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <dinput.h>

#include "Sprite.h"
#include "GameLog.h"
#include "IInput.h"
#include "GameInput.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "TestScene.h"

#define KEYBOARD_BUFFERD_SIZE 1024

class Game : public IInput
{
public:
    Game(int fps = 60, int width = 960, int height = 640);
    ~Game();

protected:

    PDIRECT3DSURFACE9       mBackground,
                            mBackBuffer;

    int                     mWidth,
                            mHeight;
    static int              mIsDone;
    float                   mFPS;

    //khoi tao vong lap cho game
    void InitLoop();

    //init input cho game
    void InitInput();

    //ham dung de ve sau khi update
    void Render();

    //ham load content duoc goi khi khoi tao game va chi goi 1 lan
    void LoadContent();  

    //ham update cua game
    void Update(float dt);

    //ham nhan su kien khi co keydown
    void OnKeyDown(int keyCode);

    //ham nhan su kien khi co keyup
    void OnKeyUp(int keyCode);

    //su kien Mouse Down
    void OnMouseDown(float x, float y);

    void OnMouseMove(float x, float y);

    void OnMouseUp(float x, float y);

    LPDIRECT3DSURFACE9 createSurfaceFromFile(LPDIRECT3DDEVICE9 device, LPWSTR filePath);
};

#endif