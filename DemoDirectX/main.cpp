#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <dinput.h>
#include <windowsx.h>
#include "Sprite.h"
#include "Game.h"
#include "GameLog.h"
#include "SceneManager.h"
#include "GameInput.h"


using namespace std;

#define WIN_NAME L"Demo Beizer Curve"
#define WIN_TITLE L"Demo Beizer Curve"
#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 650
#define FPS 60
#define KEYBOARD_BUFFERD_SIZE 1024

/*

*/
int initWindow(int cmdShow);
int InitDevice();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LPDIRECT3D9             mDirect3D9;
LPD3DXSPRITE            mSpriteHandler;
PDIRECT3D9              mD3d;
LPDIRECT3DDEVICE9       mDevice;
HINSTANCE               mHInstance;
int                     mCmdShow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    mHInstance = hInstance;
    initWindow(cmdShow);
    return 0;
}

int initWindow(int cmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = mHInstance;

    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WIN_NAME;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    RECT rect;	// the rect represents for client area of the window
    rect.left = 100;
    rect.right = 100 + SCREEN_WIDTH;
    rect.top = 100;
    rect.bottom = 100 + SCREEN_HEIGHT;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    //WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
    HWND hWnd = CreateWindow(
        WIN_NAME,    // create a handle window object by createWindow function
        WIN_NAME,
        WS_OVERLAPPEDWINDOW,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
        NULL,
        NULL,
        wc.hInstance,
        NULL);

    //HWND hWnd = CreateWindow(
    //    WIN_NAME,
    //    WIN_NAME,
    //    WS_OVERLAPPEDWINDOW,
    //    CW_USEDEFAULT,
    //    CW_USEDEFAULT,
    //    SCREEN_WIDTH,
    //    SCREEN_HEIGHT,
    //    NULL,
    //    NULL,
    //    mHInstance,
    //    NULL);

    if (!hWnd)
    {
        DWORD errCode = GetLastError();
        GAMELOG("[Error] Create Windows failed");
    }

    GameGlobal::SetCurrentHINSTACE(mHInstance);
    GameGlobal::SetCurrentHWND(hWnd);

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    if (InitDevice())
        Game *game = new Game(60, SCREEN_WIDTH, SCREEN_HEIGHT);

    return 0;
}

int InitDevice()
{
    mD3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    //d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    //d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //d3dpp.EnableAutoDepthStencil = true;
    //d3dpp.hDeviceWindow = mHwnd;

    HRESULT dvresult = mD3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        GameGlobal::getCurrentHWND(),
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &mDevice);
    GameGlobal::SetCurrentDevice(mDevice);

#if _DEBUG
    switch (dvresult)
    {
    case D3DERR_INVALIDCALL:
        GAMELOG("[Error] Direct3DCreate9 parameters are wrong");
        return 0;


    case D3DERR_NOTAVAILABLE:
        GAMELOG("[Error] Direct3DCreate9 doesn't support this call");
        return 0;

    case D3DERR_OUTOFVIDEOMEMORY:
        GAMELOG("[Error] Direct3DCreate9 video card isn't enough memory");
        return 0;

    case D3D_OK: default:
        break;
    }
#endif    

    D3DXCreateSprite(GameGlobal::GetCurrentDevice(), &mSpriteHandler);
    GameGlobal::SetCurrentSpriteHandler(mSpriteHandler);
    //mDevice->CreateOffscreenPlainSurface(100, 100, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &mBackground, NULL);

    return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            GameGlobal::isGameRunning = false;
            PostQuitMessage(0);
            break;

        case WM_LBUTTONDOWN:
            GameInput::GetInstance()->OnMouseDown((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
            //InvalidateRgn(hWnd, NULL, TRUE);
            break;

        case WM_LBUTTONUP:
            GameInput::GetInstance()->OnMouseUp((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
            break;
            
        case WM_MOUSEMOVE:
            GameInput::GetInstance()->OnMouseMove((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}