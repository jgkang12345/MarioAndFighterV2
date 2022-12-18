#include "pch.h"
#include "PlayerJumpAnimation.h"

Sprite* PlayerJumpAnimation::Jumping()
{
	if (m_nowFrame >= 2)
		m_nowFrame = 2;

	Sprite* ret = m_clips[m_nowFrame];
	m_nowFrame = (m_nowFrame + 1) % m_clips.size();

	return ret;
}

Sprite* PlayerJumpAnimation::JumpEnd()
{
	if (m_nowFrame >= 7)
		m_nowFrame = 7;

	Sprite* ret = m_clips[m_nowFrame];
	m_nowFrame = (m_nowFrame + 1) % m_clips.size();

	return ret;
}

Sprite* PlayerJumpAnimation::JumpDone()
{
	return m_clips[m_clips.size() - 1];
	Init();
}
