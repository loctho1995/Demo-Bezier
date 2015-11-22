#ifndef __GAME_LOG__H__
#define __GAME_LOG__H__
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

//Show and save game logs
#define GAMELOG(s,...) saveLog(s , ##__VA_ARGS__)
//#define GAMELOG(s,...) saveLog(s, ##__VA_ARGS__)

void saveLog(const LPCSTR s, ...);
void loadFile();
static FILE *mFile;

#endif