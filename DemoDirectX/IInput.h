#pragma once
//truyen input thong qua interface
__interface IInput
{
    virtual void OnKeyDown(int keyCode);
    virtual void OnKeyUp(int keyCode);
    virtual void OnMouseDown(float x, float y);
    virtual void OnMouseUp(float x, float y);
    virtual void OnMouseMove(float x, float y);
    //virtual void ProcessInput(BYTE keyStatee[]);
}; 
