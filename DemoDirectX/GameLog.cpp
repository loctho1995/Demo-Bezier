#include "GameLog.h"
#include <fstream>
#include <iostream>

const char *LOG_FILE = "gamelog.log";
static int mIsLoaded = 0;

#pragma warning (disable:4996)

//send log to output
#define OUTLOG(s)  \
{                   \
    std::ostringstream os;\
    os << s << endl;\
    OutputDebugStringA(os.str().c_str());   \
}

/*
std::ostringstream os;
os << s;
OutputDebugStringA(os.str().c_str());   \
*/
void saveLog(const LPCSTR s, ...)
{
    //size_t buffsize = strlen(s) * sizeof(char);
    char buff[1024];
    int length = strlen(s);

    va_list ap;
    va_start(ap, s);
    _vsnprintf(buff, sizeof(buff), s, ap); //sizeof(szBuff)
    va_end(ap);

    OUTLOG(buff);

    if (!mIsLoaded)
        loadFile();

    if (mFile)
    {
        if (!mIsLoaded)
        {
            mIsLoaded = 1;

            //get current time
            time_t now = time(0);
            struct tm tstruct;
            tstruct = *localtime(&now);
            char buf[80];
            strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);

            fprintf_s(mFile, "--->");
            fprintf_s(mFile, buf);
            fprintf_s(mFile, "<---");
            fprintf(mFile, "\n");
        }

        fprintf(mFile, buff);
        fprintf(mFile, "\n");
        fclose(mFile);
    }
    else
        OUTLOG("Open file failed!");
}

void loadFile()
{
    fopen_s(&mFile, LOG_FILE, "a");
}