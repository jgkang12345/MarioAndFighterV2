#include "pch.h"
#include "NefendesStandOffWeapon.h"
#include "GameWnd.h"
#include "Animation.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Bitmap.h"
#include "Map.h"
#include <list>
#include "Monster.h"
NefendesStandOffWeapon::~NefendesStandOffWeapon()
{
	if (m_missile)
		delete m_missile;
}

void NefendesStandOffWeapon::Update(Map* _map, Player* player)
{
	m_pos.x += m_hPower;

	switch (_map->GetTileType(m_pos))
	{
	case EMPTYType:
		break;
	case WALLType:
		m_isDead = true;
		break;
	case PlayerType:
		break;
	case NefendesType:
		break;
	case GhostType:
		break;
	case KumaType:
		break;
	case NefendesRect:
		break;
	case GhostRect:
		break;
	default:
		break;
	}

	if (player->IsCrash(m_boundRect))
		m_isDead = true;
}

void NefendesStandOffWeapon::Render(GameWnd* _wnd, Player* player)
{
	Sprite* sprite = m_missile->GetFrame();
	const int width = abs((int)(sprite->GetRect().left - sprite->GetPivot().x));
	const int height = abs((int)(sprite->GetRect().top - sprite->GetPivot().y));
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_boundRect = dest;
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(player->GetFilePath(), _wnd->GetRRT())->GetBitmap(), dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sprite->GetRect());
}
