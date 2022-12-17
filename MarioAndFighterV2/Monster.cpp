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
