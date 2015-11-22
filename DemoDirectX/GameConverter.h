#pragma once
#ifndef __GAME_CONVERTER__
#define __GAME_CONVERTER__

#include <d3dx9.h>
#include <d3d9.h>
#include "GameLog.h"


class GameConverter
{
public:
    static wchar_t* CharToWSTR(const char* input);
    static wchar_t* StringToWSTR(const std::string input);
    GameConverter();
    ~GameConverter();
};


#endif
