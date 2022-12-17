#include "pch.h"
#include "FPSManager.h"

FPSManager fpsManager(50);

FPSManager::FPSManager(int _targetFps)
{
	m_targetFps = _targetFps;
	m_currentTIck = 0;
	m_lastTick = 0;
	m_lastFrameTick = 0;
	m_sumTick = 0;
}

FPSManager::~FPSManager()
{
	// ¼Ò¸ê
}


bool FPSManager::Ok()
{
	m_lastTick = m_currentTIck;
	m_currentTIck = timeGetTime();
	m_sumTick += m_currentTIck - m_lastTick;
	if (m_sumTick >= m_targetFps)
	{
		m_sumTick = 0;
		return true;
	}
	else
	{
		return false;
	}
}
