#ifndef __GAME_DEBUG_DRAW__
#define __GAME_DEBUG_DRAW__
#include <d3dx9.h>
#include <d3d9.h>

class GameDebugDraw 
{
public:
    GameDebugDraw(LPD3DXSPRITE spriteHandler);
    void Draw();
    void DrawLine(D3DXVECTOR2 lines[], int count);
    void DrawRect(RECT rect);
    LPD3DXLINE LineDraw;
    //set do rong cua duong ve, mac dinh = 10
    void setLineSize(float width);
    void setColor(D3DCOLOR color);
    ~GameDebugDraw();

private:
    LPD3DXSPRITE mSpriteHandler;
    LPDIRECT3DDEVICE9 mddv;
    D3DCOLOR mColor;
};

#endif

