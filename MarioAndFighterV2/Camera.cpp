#include "pch.h"
#include "Camera.h"
#include "Player.h"
#include "Map.h"
void Camera::Init(const int& _x, const int& _y, Map* _map)
{
	int c_left = _x - cameraW;
	int c_top = _y - cameraH;
	int c_width = _x + cameraW;
	int c_height = _y + cameraH;
	if (c_left < 0)
	{
		c_left = 0;
		c_width = cameraW * 2;
	}
	if (c_top < 0)
	{
		c_top = 0;
		c_height = cameraH * 2;
	}
	if (c_width > (_map->GetXSize()) * TILESIZE)
	{
		c_width = (_map->GetXSize()) * TILESIZE;
	}
	if (c_height > (_map->GetYSize()) * TILESIZE)
	{
		c_height = (_map->GetYSize()) * TILESIZE;
	}
	D2D1_RECT_F cameraZone = { c_left, c_top, c_width, c_height };
	SetCameraRect(cameraZone);
}

void Camera::Update(Player* _player, Map* _map, GAME_TYPE _type)
{
	switch (_type)
	{
	case OVERWORLD:
		if (!IsCrash(_player, _map))
		{
			int hPower = _player->GetHPower();
			int vPower = _player->GetVPower();

			int c_left = m_cameraRect.left + (hPower * 1);
			int c_top = m_cameraRect.top + (vPower * 1);
			int c_width = m_cameraRect.right + (hPower * 1);
			int c_height = m_cameraRect.bottom + (vPower * 1);
			D2D1_RECT_F cameraZone = { c_left, c_top, c_width, c_height };
			m_cameraRect = cameraZone;
		}
		break;

	case BATTLE:
		D2D1_RECT_F cameraZone = { 0, 0, 239, 159 };
		m_cameraRect = cameraZone;
		break;
	}
}

bool Camera::IsCrash(Player* _player, Map* _map)
{
	bool ret = false;
	int hPower = _player->GetHPower();
	int vPower = _player->GetVPower();

	if (m_cameraRect.left + hPower < 0 && hPower == -powerX)
	{
		ret = true;
	}
	if (m_cameraRect.top + vPower < 0 && vPower == -powerY)
	{
		ret = true;
	}
	if (m_cameraRect.right + hPower >= (_map->GetXSize()) * TILESIZE && hPower == powerX)
	{
		ret = true;
	}
	if (m_cameraRect.bottom + vPower >= (_map->GetYSize()) * TILESIZE && vPower == powerY)
	{
		ret = true;
	}

	return ret;
}

Camera::~Camera()
{
}

