#include "pch.h"
#include "MarioAndFighterApp.h"

int APIENTRY _tWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstace, LPTSTR _lpCmdLine, int _nCmdShow)
{
	MarioAndFighterApp app;
	app.Init(_hInstance, _T("MarioAndFighter"), _T("MarioAndFighter"), 500, 500, _nCmdShow);
	return app.Dispatch();
}