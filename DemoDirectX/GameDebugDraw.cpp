#include "GameDebugDraw.h"


GameDebugDraw::GameDebugDraw(LPD3DXSPRITE spriteHandler)
{
    mSpriteHandler = spriteHandler;
    mSpriteHandler->GetDevice(&mddv);
    D3DXCreateLine(mddv, &LineDraw);
    LineDraw->SetWidth(10);
    mColor = D3DCOLOR_XRGB(71, 85, 119);
    
}

GameDebugDraw::~GameDebugDraw()
{
}

void GameDebugDraw::Draw()
{

}

void GameDebugDraw::setLineSize(float width)
{
    LineDraw->SetWidth(width);
}

void GameDebugDraw::DrawLine(D3DXVECTOR2 lines[], int count)
{
    LineDraw->Begin();
    LineDraw->Draw(lines, count, mColor);
    LineDraw->End();
}

void GameDebugDraw::DrawRect(RECT rect)
 {
    D3DXVECTOR2 lines[] = { D3DXVECTOR2(rect.left, rect.top), 
                            D3DXVECTOR2(rect.right, rect.top), 
                            D3DXVECTOR2(rect.right, rect.bottom), 
                            D3DXVECTOR2(rect.left, rect.bottom), 
                            D3DXVECTOR2(rect.left, rect.top) };

    DrawLine(lines, 5);
}

void GameDebugDraw::setColor(D3DCOLOR color)
{
    mColor = color;
}