#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Sprite.h"
#include "GameWnd.h"
#include "Bitmap.h"
#include "Map.h"
#include "Camera.h"
#include "SceneManager.h"
#include "GameScene.h"
animationSqList
enum PLAYER_ANIMATION_TYPE : int 
{
	OVERWORLD_RIGHT_MOVE = 0,	
	OVERWORLD_DOWN_MOVE = 1,
	OVERWORLD_TOP_MOVE = 2,
	OVERWORLD_IDLE = 3,
	BATTLE_ATTACK = 4,
	BATTLE_IDLE = 5,
	BATTLE_STAND_OFF_ATTACK = 6,
	BATTLE_JUMP = 7
};

Player::Player(const char* _imgKey, const char* _bitmapKey) :GameObject(PlayerObj)
{
	SetImgKey(_imgKey);
	SetBitmapKey(_bitmapKey);
	m_animation_vector.resize(PLAYER_ANIMATION_COUNT);
	for (int animation = 0; animation < PLAYER_ANIMATION_COUNT; animation++)
		m_animation_vector[animation] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(AnimationSeq[animation]));
	m_lastSprite = m_animation_vector[OVERWORLD_IDLE]->GetFirst();
}

Player::~Player()
{
	for (auto& item : m_animation_vector)
		if (item)
			delete item;
}

void Player::Update(Map* _map, GAME_TYPE _type, std::vector<Map*>& _mapLIst, GameWnd* _wnd)
{
	switch (_type)
	{
	case OVERWORLD:
		OVERWORLDUpdate(_map, _mapLIst, _wnd);
		break;

	case BATTLE:
		BATTLEUpdate(_map, _mapLIst, _wnd);
		break;
	}
}

void Player::OVERWORLDUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd)
{
	bool mapNext = false;

	Pos prevPos = m_pos;
	Pos nextPos = { m_pos.x + m_hPower , m_pos.y + m_vPower };

	switch (_map->GetTileType(nextPos))
	{
	case EMPTYType:
		m_pos = nextPos;
		break;
	case WALLType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case PlayerType:
		m_pos = nextPos;
		break;
	case NefendesType:
		m_vPower = 0;
		m_hPower = 0;
		mapNext = true;
		break;
	case GhostType:
		m_vPower = 0;
		m_hPower = 0;
		// mapNext = true;
		break;
	case KumaType:
		m_vPower = 0;
		m_hPower = 0;
		// mapNext = true;
		break;
	case NefendesRect:
		m_vPower = 0;
		m_hPower = 0;
		mapNext = true;
		break;
	case GhostRect:
		m_vPower = 0;
		m_hPower = 0;
		// mapNext = true;
		break;
	}

	if (mapNext)
	{
		mapSqList
		m_mapSeq = m_mapSeq + 1;
		if (m_mapSeq < MAP_COUNT)
		{
			char target[] = "battle";
			SceneManager::GetInstance()->SetSceen(LOADING);
			_mapLIst[m_mapSeq] = new Map(mapSq[m_mapSeq], this, _wnd);
			if (NULL != strstr(_mapLIst[m_mapSeq]->GetFileName(), target))
				SceneManager::GetInstance()->GetGameScene()->SetGameType(BATTLE);
			else 
				SceneManager::GetInstance()->GetGameScene()->SetGameType(OVERWORLD);
			m_camera = new Camera(this->GetPos().x, this->GetPos().y, _mapLIst[m_mapSeq]);
			m_dir = Dir::NONE;
		}
		else
		{
			m_mapSeq--;
		}
	}
}

void Player::BATTLEUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd)
{
}

void Player::Render(GameWnd* _wnd, GAME_TYPE _type)
{
	switch (_type)
	{
	case OVERWORLD:
		OVERWORLDRender(_wnd);
		break;

	case BATTLE:
		BATTLERender(_wnd);
		break;
	}
}

void Player::OVERWORLDRender(GameWnd* _wnd)
{
	if (!m_isStop)
	{
		switch (m_dir)
		{
		case UP:
			m_lastSprite = m_animation_vector[OVERWORLD_TOP_MOVE]->GetFrame();
			m_isRotation = false;
			break;
		case RIGHT:
			m_lastSprite = m_animation_vector[OVERWORLD_RIGHT_MOVE]->GetFrame();
			m_isRotation = false;
			break;
		case DOWN:
			m_lastSprite = m_animation_vector[OVERWORLD_DOWN_MOVE]->GetFrame();
			m_isRotation = false;
			break;
		case LEFT:
			m_lastSprite = m_animation_vector[OVERWORLD_RIGHT_MOVE]->GetFrame();
			m_isRotation = true;
			break;
		case NONE:
			break;
		}
	}
	CommonRender(_wnd, m_lastSprite, m_isRotation, m_imgKey);
}

void Player::BATTLERender(GameWnd* _wnd)
{
}

void Player::CommonRender(GameWnd* _wnd, Sprite* _sprite, bool _isRotation, char* _key)
{
	const int width = abs((int)(_sprite->GetRect().left - _sprite->GetPivot().x));
	const int height = abs((int)(_sprite->GetRect().top - _sprite->GetPivot().y));
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_boundRect = dest;
	FLOAT opacity = m_damaged ? 0.5f : 1.0f;
	if (_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(m_pos.x, m_pos.x)));
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(_key, _wnd->GetRRT())->GetBitmap(), dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, _sprite->GetRect());
	if (_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_damaged = false;
}

void Player::KeyUpBind(WPARAM _wparam, GAME_TYPE _type)
{
	switch (_wparam)
	{
	case VK_UP:
		if (m_dir == Dir::UP)
		{
			m_vPower = 0;
			m_hPower = 0;
			m_isStop = true;
		}
		break;

	case VK_RIGHT:
		if (m_dir == Dir::RIGHT)
		{
			m_vPower = 0;
			m_hPower = 0;
			m_isStop = true;
		}
		break;

	case VK_DOWN:
		if (m_dir == Dir::DOWN)
		{
			m_vPower = 0;
			m_hPower = 0;
			m_isStop = true;
		}
		break;

	case VK_LEFT:
		if (m_dir == Dir::LEFT)
		{
			m_vPower = 0;
			m_hPower = 0;
			m_isStop = true;
		}
		break;
	}
}

void Player::KeyDownBind(WPARAM _param, GAME_TYPE _type)
{
	switch (_param)
	{
	case VK_UP:
		m_dir = Dir::UP;
		m_vPower = -powerY;
		m_hPower = 0;
		m_isStop = false;
		break;

	case VK_RIGHT:
		m_dir = Dir::RIGHT;
		m_hPower = powerY;
		m_vPower = 0;
		m_isStop = false;
		break;

	case VK_DOWN:
		m_dir = Dir::DOWN;
		m_vPower = powerY;
		m_hPower = 0;
		m_isStop = false;
		break;

	case VK_LEFT:
		m_dir = Dir::LEFT;
		m_hPower = -powerY;
		m_vPower = 0;
		m_isStop = false;
		break;

	case A:
		if (_type == OVERWORLD || m_attack == ATTACK_ING)
			break;
		if (m_attack == ATTACK_NONE)
			m_attack = ATTACK_START;
		break;

	case S:
		if (_type == OVERWORLD || m_attack == ATTACK_STAND_OFF_ING)
			break;
		if (m_attack == ATTACK_NONE)
			m_attack = ATTACK_STAND_OFF_START;
		break;

	case D:
		if (_type == BATTLE && m_jump == JUMP_NONE)
			m_jump = JUMP_UP;
		break;
	}
}

bool Player::IsCrash(const D2D1_RECT_F& _rect)
{
	if (m_boundRect.left > _rect.right || m_boundRect.right < _rect.left || m_boundRect.top > _rect.bottom || m_boundRect.bottom < _rect.top)
		return false;
	else
	{
		m_damaged = true;
		return true;
	}
}
