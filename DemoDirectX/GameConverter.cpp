#include "GameConverter.h"


GameConverter::GameConverter()
{
}


GameConverter::~GameConverter()
{
}

wchar_t* GameConverter::CharToWSTR(const char* input)
{
    size_t wn = mbsrtowcs(NULL, &input, 0, NULL);

    wchar_t * buf = new wchar_t[wn + 1]();  // value-initialize to 0 (see below)

    wn = mbsrtowcs(buf, &input, wn + 1, NULL);

    return buf;
}

wchar_t* GameConverter::StringToWSTR(const std::string input)
{
    return CharToWSTR(input.c_str());
}
