#include "pch.h"
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 100);