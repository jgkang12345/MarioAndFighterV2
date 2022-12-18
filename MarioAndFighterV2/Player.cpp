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
#include "PlayerJumpAnimation.h"
#include "Monster.h"
#include "PlayerStandOffWeapon.h"
#include "HPBar.h"
#include "Nefendes.h"
animationSqList
enum PLAYER_ANIMATION_TYPE : int 
{
	OVERWORLD_RIGHT_MOVE = 0,	
	OVERWORLD_DOWN_MOVE = 1,
	OVERWORLD_TOP_MOVE = 2,
	OVERWORLD_IDLE = 3,
	BATTLE_ATTACK = 4,
	BATTLE_IDLE = 5,
	BATTLE_MOVE = 6,
	BATTLE_STAND_OFF_ATTACK = 7,
	BATTLE_JUMP = 8
};

Player::Player(const char* _imgKey, const char* _bitmapKey) :GameObject(PlayerObj)
{
	SetImgKey(_imgKey);
	SetBitmapKey(_bitmapKey);
	m_animation_vector.resize(PLAYER_ANIMATION_COUNT);
	for (int animation = 0; animation < PLAYER_ANIMATION_COUNT; animation++)
	{
		if (animation == BATTLE_JUMP)
			m_animation_vector[animation] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(AnimationSeq[animation]));
		else 
			m_animation_vector[animation] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryDataPlayerJump(AnimationSeq[animation]));
	}
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
			{
				SceneManager::GetInstance()->GetGameScene()->SetGameType(BATTLE);
				m_lastSprite = m_animation_vector[BATTLE_IDLE]->GetFirst();
			}	
			else
			{
				SceneManager::GetInstance()->GetGameScene()->SetGameType(OVERWORLD);
				m_lastSprite = m_animation_vector[OVERWORLD_IDLE]->GetFirst();
			}				
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
	bool mapNext = false;
	const int bottomLine = _map->GetPlayerStartPos().y;
	const int topLine = _map->GetPlayerStartPos().y - JUMP_MAX;

	if (m_HPbar == nullptr)
		m_HPbar = new HPBar(this);


	Pos prevPos = m_pos;
	int g = -2;
	switch (m_jump)
	{
	case JUMP_UP:
		m_vPower -= JUMP_POWER;
		break;

	case JUMP_END:
		m_vPower = 0;
		m_jump = JUMP_DOWN;
		break;

	case JUMP_DOWN:
		m_vPower += (JUMP_POWER + 1);
		break;

	case JUMP_DONE:
		m_vPower = 0;
		m_jump = JUMP_NONE;
		break;
	}

	int y = m_pos.y + m_vPower;

	if (y > bottomLine)
	{
		y = bottomLine;
		m_jump = JUMP_DONE;
	}
	if (y < topLine)
	{
		y = topLine;
		m_jump = JUMP_END;
	}

	Pos nextPos = { m_pos.x + m_hPower , y };
	
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
		// mapNext = true;
		break;
	case GhostRect:
		m_vPower = 0;
		m_hPower = 0;
		// mapNext = true;
		break;
	}

	for (auto it = begin(m_missiles); it != end(m_missiles);)
	{
		if ((*it)->IsDead())
		{
			delete* it;
			it = m_missiles.erase(it);
		}
		else
		{
			(*it)->Update(_map, _mapLIst);
			it++;
		}
	}
}

void Player::Render(GameWnd* _wnd, Map* _map, GAME_TYPE _type)
{
	switch (_type)
	{
	case OVERWORLD:
		OVERWORLDRender(_wnd, _map);
		break;

	case BATTLE:
		BATTLERender(_wnd, _map);
		break;
	}
}

void Player::OVERWORLDRender(GameWnd* _wnd, Map* _map)
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

void Player::BATTLERender(GameWnd* _wnd, Map* _map)
{
	if (!m_isStop) 
	{
		switch (m_dir)
		{
		case RIGHT:
			m_lastSprite = m_animation_vector[BATTLE_MOVE]->GetFrame();
			m_isRotation = false;
			break;
		case LEFT:
			m_lastSprite = m_animation_vector[BATTLE_MOVE]->GetFrame();
			m_isRotation = true;
			break;
		}
	}
	else
	{
		m_lastSprite = m_animation_vector[BATTLE_IDLE]->GetFirst();
	}
	
	switch (m_jump)
	{
	case JUMP_UP:
		m_lastSprite = reinterpret_cast<PlayerJumpAnimation*>(m_animation_vector[BATTLE_JUMP])->Jumping();
		break;

	case JUMP_END:
		m_lastSprite = reinterpret_cast<PlayerJumpAnimation*>(m_animation_vector[BATTLE_JUMP])->Jumping();
		break;

	case JUMP_DOWN:
		m_lastSprite = reinterpret_cast<PlayerJumpAnimation*>(m_animation_vector[BATTLE_JUMP])->JumpEnd();
		break;

	case JUMP_DONE:
		m_lastSprite = reinterpret_cast<PlayerJumpAnimation*>(m_animation_vector[BATTLE_JUMP])->JumpDone();
		break;
	}

	switch (m_attack)
	{
	case ATTACK_START:
		m_attack = ATTACK_ING;
		break;

	case ATTACK_ING:
		m_lastSprite = m_animation_vector[BATTLE_ATTACK]->GetFrameNoAuto();
		if (m_animation_vector[BATTLE_ATTACK]->GetFrameCount() == m_animation_vector[BATTLE_ATTACK]->GetNowFrame())
		{
			if (_map->GetMonster()->IsCrash(m_boundRect))
			{
				switch (_map->GetMonster()->GetObjectType())
				{
				case NefendesObj:
					reinterpret_cast<Nefendes*>(_map->GetMonster())->Attacked(m_damage);
					break;
		
				}
			}
			m_animation_vector[BATTLE_ATTACK]->Init();
			m_attack = ATTACK_NONE;
			m_lastSprite = m_animation_vector[BATTLE_IDLE]->GetFirst();
		}
		break;

	case ATTACK_STAND_OFF_START:
		m_attack = ATTACK_STAND_OFF_ING;
		break;

	case ATTACK_STAND_OFF_ING:
		m_lastSprite = m_animation_vector[BATTLE_STAND_OFF_ATTACK]->GetFrameNoAuto();
		if (m_animation_vector[BATTLE_STAND_OFF_ATTACK]->GetFrameCount() == m_animation_vector[BATTLE_STAND_OFF_ATTACK]->GetNowFrame())
		{
			const int height = m_lastSprite->GetRect().bottom - m_lastSprite->GetRect().top;
			PlayerStandOffWeapon* missile = new PlayerStandOffWeapon();
			missile->SetPos({ m_pos.x, (m_pos.y + (m_pos.y - height)) / 2 });
			if (m_isRotation)
				missile->SetHPower(-5);
			else
				missile->SetHPower(5);
			Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("missile.spr"));
			missile->SetMissileAnimation(missileAnimation);
			m_missiles.push_back(missile);
			m_animation_vector[BATTLE_STAND_OFF_ATTACK]->Init();
			m_attack = ATTACK_NONE;
			m_lastSprite = m_animation_vector[BATTLE_IDLE]->GetFirst();
		}
		break;
	}

	if (m_HPbar)
		m_HPbar->Render(_wnd);
	CommonRender(_wnd, m_lastSprite, m_isRotation, m_bitmapKey);
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
	switch (_type)
	{
	case OVERWORLD:
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
		break;
	case BATTLE:
		switch (_wparam)
		{
		case VK_RIGHT:
			if (m_dir == Dir::RIGHT)
			{
				m_hPower = 0;
				m_isStop = true;
			}
			break;
		case VK_LEFT:
			if (m_dir == Dir::LEFT)
			{
				m_hPower = 0;
				m_isStop = true;
			}
			break;
		}
		break;
	}
}

void Player::KeyDownBind(WPARAM _param, GAME_TYPE _type)
{

	switch (_type)
	{
	case OVERWORLD:
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
		break;
	case BATTLE:
		switch (_param)
		{
		case VK_RIGHT:
			m_dir = Dir::RIGHT;
			m_hPower = powerY;
			m_isStop = false;
			break;

		case VK_LEFT:
			m_dir = Dir::LEFT;
			m_hPower = -powerY;
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


void Player::Attacked(int damage) 
{
	m_hp -= damage;
	m_HPbar->Update();
}