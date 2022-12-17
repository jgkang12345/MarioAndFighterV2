#pragma once
/***********************************************
	FPSManager: FPS °ü¸®
***********************************************/
class FPSManager
{
private:
	int m_targetFps;
	int m_nowFps;
	int m_sumTick;
	int m_currentTIck;
	int m_lastTick;
	int m_lastFrameTick;
public:
	FPSManager(int _targetFps);
	~FPSManager();
	bool Ok();
};

extern FPSManager fpsManager;