#include "pch.h"
#include "HPBar.h"
#include "GameObject.h"
#include "Monster.h"
#include "GameWnd.h"
#include "Player.h"
#include "Nefendes.h"
#include "Ghost.h"
enum WNDCOLOR 
{
	RED = 1,
	GREEN = 2
};

const int HPBAR_WDITH = 15;
const int FIX_RIGHT = 30;
const int PLAYER_MAX_HP = 150;
const int NEFENDES_MAX_HP = 200;
const int GHOST_MAX_HP = 250;
HPBar::HPBar(GameObject* object) : m_object(object)
{
	switch (m_object->GetObjectType())
	{
	case PlayerObj:
	{
		m_ca = 30;
		Player* player = reinterpret_cast<Player*>(m_object);
		Pos pos = player->GetPos();
		m_hpRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + m_ca,15 };
		m_hpMaxRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + 30,15 };
		break;
	}
	case NefendesObj:
	{
		m_ca = 30;
		Nefendes* nefendes = reinterpret_cast<Nefendes*>(m_object);
		Pos pos = nefendes->GetPos();
		m_hpRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + m_ca,15 };
		m_hpMaxRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + 30,15 };
		break;
	}
	case GhostObj:
	{
		m_ca = 30;
		Nefendes* nefendes = reinterpret_cast<Nefendes*>(m_object);
		Pos pos = nefendes->GetPos();
		m_hpRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + m_ca,15 };
		m_hpMaxRect = { (FLOAT)pos.x,10,(FLOAT)pos.x + 30,15 };
		break;
	}
	}
}

void HPBar::Render(GameWnd* _wnd)
{
	switch (m_object->GetObjectType())
	{
	case PlayerObj:
	{
		Player* player = reinterpret_cast<Player*>(m_object);
		Pos pos = player->GetPos();
		m_hpRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 40,(FLOAT)pos.x + m_ca - HPBAR_WDITH,(FLOAT)pos.y - 35 };
		m_hpMaxRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 40,(FLOAT)pos.x + FIX_RIGHT - HPBAR_WDITH,(FLOAT)pos.y - 35 };

		_wnd->HPRender(m_hpMaxRect, RED);
		_wnd->HPRender(m_hpRect, GREEN);
		break;
	}
	case NefendesObj:
	{
		Nefendes* nefendes = reinterpret_cast<Nefendes*>(m_object);
		Pos pos = nefendes->GetPos();
		m_hpRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 50,(FLOAT)pos.x + m_ca - HPBAR_WDITH,(FLOAT)pos.y - 45 };
		m_hpMaxRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 50,(FLOAT)pos.x + FIX_RIGHT - HPBAR_WDITH,(FLOAT)pos.y - 45 };

		_wnd->HPRender(m_hpMaxRect, RED);
		_wnd->HPRender(m_hpRect, GREEN);
		break;
	}
	
	case GhostObj:
	{
		Nefendes* nefendes = reinterpret_cast<Nefendes*>(m_object);
		Pos pos = nefendes->GetPos();
		m_hpRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 70,(FLOAT)pos.x + m_ca - HPBAR_WDITH,(FLOAT)pos.y - 65 };
		m_hpMaxRect = { (FLOAT)pos.x - HPBAR_WDITH,(FLOAT)pos.y - 70,(FLOAT)pos.x + FIX_RIGHT - HPBAR_WDITH,(FLOAT)pos.y - 65 };

		_wnd->HPRender(m_hpMaxRect, RED);
		_wnd->HPRender(m_hpRect, GREEN);
		break;
	}

	}
}

void HPBar::Update()
{
	switch (m_object->GetObjectType())
	{
	case PlayerObj:
		{
			Player* player = reinterpret_cast<Player*>(m_object);
			const int maxHp = PLAYER_MAX_HP;
			int hp = player->GetHp();
			m_ca = FIX_RIGHT * (static_cast<FLOAT>(hp) / static_cast<FLOAT>(maxHp));
			if (m_ca <= 0)
				m_ca = 0;
			break;	
		}

	case NefendesObj:
	{
		Nefendes* nefendes = reinterpret_cast<Nefendes*>(m_object);
		const int maxHp = NEFENDES_MAX_HP;
		int hp = nefendes->GetHp();
		m_ca = FIX_RIGHT * (static_cast<FLOAT>(hp) / static_cast<FLOAT>(maxHp));
		if (m_ca <= 0)
			m_ca = 0;
		break;
	}

	case GhostObj:
	{
		Ghost* ghost = reinterpret_cast<Ghost*>(m_object);
		const int maxHp = GHOST_MAX_HP;
		int hp = ghost->GetHp();
		m_ca = FIX_RIGHT * (static_cast<FLOAT>(hp) / static_cast<FLOAT>(maxHp));
		if (m_ca <= 0)
			m_ca = 0;
		break;
	}

	}
}
