#include "pch.h"
#include "Monster.h"
#include "GameWnd.h"

Monster::Monster(OBJECT_TYPE _type, GameWnd* _wnd) : GameObject(_type)
{

}

Monster::~Monster()
{
	for (auto& item : m_animation_vector)
		if (item)
			delete item;
}

bool Monster::IsCrash(const D2D1_RECT_F& _rect)
{
	if (m_boundRect.left > _rect.right || m_boundRect.right < _rect.left || m_boundRect.top > _rect.bottom || m_boundRect.bottom < _rect.top)
		return false;
	else
	{
		m_damaged = true;
		return true;
	}
}
