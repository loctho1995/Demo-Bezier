#include "GameInput.h"

GameInput* GameInput::mInstance = NULL;

GameInput::GameInput()
{
    InitInputDevice();
    mInputUser = NULL;
}


GameInput::~GameInput()
{
}

GameInput* GameInput::GetInstance()
{
    if (!mInstance)
        mInstance = new GameInput();

#if _DEBUG
    if (mInstance == NULL)
        GAMELOG("[Error] get Keyboard instance failed");
#endif

    return mInstance;
}

void GameInput::InitInputDevice()
{
    HRESULT rs = DirectInput8Create(GameGlobal::GetCurrentHINSTACE(), 
                                    DIRECTINPUT_VERSION, 
                                    IID_IDirectInput8, 
                                    (LPVOID*)&mDI, 
                                    NULL);
#if _DEBUG
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] create input failed");
        return;
    }
    else
        GAMELOG("create input successed");
#endif

    rs = mDI->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);
#if _DEBUG
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] create Keyboard failed");
        return;
    }
    else
        GAMELOG("create Keyboard successed");
#endif

#if _DEBUG
    rs = mKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] set keyboard data format failed");
        return;
    }
    else
        GAMELOG("set keyboard data format successed");
#endif

#if _DEBUG
    mKeyboard->SetCooperativeLevel(GameGlobal::getCurrentHWND(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] set keyboard SetCooperativeLevel failed");
        return;
    }
    else
        GAMELOG("set keyboard data SetCooperativeLevel successed");
#endif

    DIPROPDWORD d;
    d.diph.dwSize = sizeof(DIPROPDWORD);
    d.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    d.diph.dwObj = 0;
    d.diph.dwHow = DIPH_DEVICE;
    d.dwData = KEYBOARD_BUFFERD_SIZE;

    mKeyboard->SetProperty(DIPROP_BUFFERSIZE, &d.diph);
#if _DEBUG
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] set keyboard Property failed");
        return;
    }
    else
        GAMELOG("set keyboard data Property successed");
#endif

    rs = mKeyboard->Acquire();
#if _DEBUG
    if (rs != D3D_OK)
    {
        GAMELOG("[Error] keyboard has been Acquired failed");
        return;
    }
    else
        GAMELOG("keyboard bas been Acquired successed");
#endif
}

void GameInput::UpdateInput()
{
    mKeyboard->GetDeviceState(sizeof(mKeyStates), (LPVOID)&mKeyStates);

    DWORD dwElements = KEYBOARD_BUFFERD_SIZE;
    HRESULT rs = mKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mKeyEvents, &dwElements, 0);

    for (DWORD i = 0; i < dwElements; i++)
    {
        int keycode = mKeyEvents[i].dwOfs;
        int keystate = mKeyEvents[i].dwData;

        if ((keystate & 0x80) > 0)
            OnKeyDown(keycode);
        else
            OnKeyUp(keycode);
    }
}

void GameInput::SetKeyboardUser(IInput *user)
{
    mInputUser = user;
}

void GameInput::OnKeyDown(int keyCode)
{
    mInputUser->OnKeyDown(keyCode);
}

void GameInput::OnMouseUp(float x, float y)
{
    mInputUser->OnMouseUp(x, y);
}

void GameInput::OnMouseMove(float x, float y)
{
    mInputUser->OnMouseMove(x, y);
}

void GameInput::OnKeyUp(int keyCode)
{
    mInputUser->OnKeyUp(keyCode);
}

int GameInput::IsKeyDown(int keyCode)
{
    return (mKeyStates[keyCode] & 0x80) > 0;
}

void GameInput::OnMouseDown(float x, float y)
{
    mInputUser->OnMouseDown(x, y);
}