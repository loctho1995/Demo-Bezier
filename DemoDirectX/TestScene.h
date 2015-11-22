#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "Scene.h"
#include "Sprite.h"
#include "GameDebugDraw.h"

class TestScene : public Scene
{
public:
    TestScene();
    ~TestScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
    void OnMouseUp(float x, float y);
    void OnMouseMove(float x, float y);
    void updateFullPoints();

    //tinh n giao thua
    unsigned int Factorial(int n);

    //tinh phuong trinh duong cong bezier
    //dung cong thuc tinh he so cua tam giac pascal
    unsigned int CalculateCoefficient(int n, int i);

    //lay diem tuong ung de ve len
    D3DXVECTOR2 CalculateSinglePoint(float t, std::vector< D3DXVECTOR2 > pointVector);

    Sprite* sprites;
    std::vector<D3DXVECTOR2> points;
    std::vector<D3DXVECTOR2> savePoints;
    std::vector<D3DXVECTOR2> fullPoints;
    float t;
    float speed; //toc do t de ve bezier (t = 0.01f / speed)
    int frameDelay; //delay frame
    int currentFrame; //dem frame hien tai
    int numSprite; //so luong sprite arrow
    int dotDistance; // khoang cach cua cac dau cham tren duong di
    int dotDistanceCounter;
    float xDistance, yDistance;
    Sprite *dot, *dot2; //sprite ve 1 cham len man hinh
    D3DXVECTOR2 previousPoint;    
    bool isPause, isDebugDraw, isHideAll, isDrawBezier, isMouseDown;
    GameDebugDraw *debugDraw, *drawBezier;

private:
    bool isContentLoaded;
    bool isClickOnNode(float x, float y, D3DXVECTOR2 point);
    int indexPointClicked;
};

