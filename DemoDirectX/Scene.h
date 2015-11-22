#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

#include "GameLog.h"
#include "IInput.h"
#include "GameInput.h"
#include "GameGlobal.h"

class Scene: public IInput
{
public:
    virtual void Update(float dt);
    virtual void LoadContent();
    virtual void Draw();
    virtual void OnKeyDown(int keyCode);
    virtual void OnKeyUp(int keyCode);
    virtual void OnMouseDown(float x, float y);
    virtual void OnMouseUp(float x, float y);
    virtual void OnMouseMove(float x, float y);
    bool IsKeyPress(int keyCode);
    D3DCOLOR GetBackcolor();

    ~Scene();

protected:
    LPD3DXSPRITE            mSpriteHandler;
    D3DCOLOR                mBackColor;
    Scene();

private :
};

#endif

