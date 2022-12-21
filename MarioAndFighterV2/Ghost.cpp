#include "pch.h"
#include "Ghost.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "GameWnd.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "HPBar.h"
#include "GhostStandOffWeapon.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Player.h"
enum GHOST_ANIMATION_TYPE : int
{
	GHOST_OVERWORLD_IDLE = 0
};

const MONSTER_PATTERN pattern1[] =
{ MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL , MONSTER_IDEL };

const MONSTER_PATTERN pattern2[] =
{ MONSTER_STAND_OFF_ATTACK, MONSTER_IDEL, MONSTER_IDEL, MONSTER_PMOVE, MONSTER_IDEL, MONSTER_PMOVE , MONSTER_IDEL };

const MONSTER_PATTERN pattern3[] =
{ MONSTER_PMOVE, MONSTER_STAND_OFF_ATTACK, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_PMOVE , MONSTER_PMOVE };

Ghost::Ghost(OBJECT_TYPE _type, GameWnd* _wnd) : Monster(_type, _wnd)
{
	Init(_wnd);
}

Ghost::~Ghost()
{
	for (auto& item : m_missiles)
		if (item)
			delete item;

	m_missiles.clear();
}

void Ghost::Init(GameWnd* _wnd)
{
	SetImgKey("Ghost.png");
	m_animation_vector.resize(NEFENDES_ANIMATION_COUNT);
	m_animation_vector[GHOST_OVERWORLD_IDLE] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("Ghost.spr"));
	m_lastFrame = m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFirst();
	ResourceManager::GetInstance()->GetBitmap(GetFilePath(), _wnd->GetRRT());
}

void Ghost::Update(Map* _map, Player* _player, GAME_TYPE _type)
{
	switch (_type)
	{
	case OVERWORLD:
		OVERWORLDUpdate(_map, _player);
		break;
	case BATTLE:
		BATTLEUpdate(_map, _player);
		break;
	}
}

void Ghost::OVERWORLDUpdate(Map* _map, Player* _player)
{
}

void Ghost::BATTLEUpdate(Map* _map, Player* _player)
{
	if (!m_isDead)
	{
		if (m_HPbar == nullptr)
			m_HPbar = new HPBar(this);

		if (m_patternQ.empty() == false)
		{
			for (auto it = begin(m_missiles); it != end(m_missiles);)
			{
				if ((*it)->IsDead())
				{
					delete* it;
					it = m_missiles.erase(it);
				}
				else
				{
					(*it)->Update(_map, _player);
					it++;
				}
			}
		}
		else
		{
			switch (dis(gen) % 3)
			{
			case 0:
				for (auto& item : pattern1)
					m_patternQ.push(item);
				break;
			case 1:
				for (auto& item : pattern2)
					m_patternQ.push(item);
				break;
			case 2:
				for (auto& item : pattern3)
					m_patternQ.push(item);
				break;
			}
		}
	}
}

void Ghost::Render(GameWnd* _wnd, GAME_TYPE _type)
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

void Ghost::OVERWORLDRender(GameWnd* _wnd)
{
	m_lastFrame = m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFrame();
	CommonRender(_wnd);
}

void Ghost::BATTLERender(GameWnd* _wnd)
{
	if (!m_isDead)
	{
		if (m_patternQ.empty())
			switch (dis(gen) % 3)
			{
			case 0:
				for (auto& item : pattern1)
					m_patternQ.push(item);
				break;
			case 1:
				for (auto& item : pattern2)
					m_patternQ.push(item);
				break;
			case 2:
				for (auto& item : pattern3)
					m_patternQ.push(item);
				break;
			}

		switch (m_patternQ.front())
		{
		case MONSTER_IDEL:
			m_lastFrame = m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFirst();
			m_patternQ.pop();
			break;

		case MONSTER_STAND_OFF_ATTACK:
			m_lastFrame = m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFrameNoAuto();

			if (m_animation_vector[GHOST_OVERWORLD_IDLE]->GetNowFrame() == m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFrameCount())
			{
				const int height = m_lastFrame->GetRect().bottom - m_lastFrame->GetRect().top;
				GhostStandOffWeapon* missile = new GhostStandOffWeapon(this);
				missile->SetPos({ m_pos.x,m_pos.y - 5 });
				if (m_isRotation)
					missile->SetHPower(5);
				else
					missile->SetHPower(-5);
				Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("GhostStandOff2.spr"));
				missile->SetMissileAnimation(missileAnimation);
				m_missiles.push_back(missile);

				m_animation_vector[GHOST_OVERWORLD_IDLE]->Init();
				m_patternQ.pop();
			}
			break;


		case MONSTER_PMOVE:
			m_lastFrame = m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFrameNoAuto();

			Pos playerPos = SceneManager::GetInstance()->GetGameScene()->GetPlayer()->GetPos();
			int dir = 1;
			if (m_pos.x > playerPos.x)
			{
				dir *= -1;
				m_dir = Dir::LEFT;
				m_isRotation = false;
			}
			else
			{
				m_dir = Dir::RIGHT;
				m_isRotation = true;
			}
		
			int move = 1;
			m_pos.x += move * dir;

			if (m_animation_vector[GHOST_OVERWORLD_IDLE]->GetNowFrame() == m_animation_vector[GHOST_OVERWORLD_IDLE]->GetFrameCount())
			{
				m_animation_vector[GHOST_OVERWORLD_IDLE]->Init();
				m_patternQ.pop();
			}
			break;
		}

		if (m_HPbar)
			m_HPbar->Render(_wnd);
	}

	CommonRender(_wnd);
}

void Ghost::CommonRender(GameWnd* _wnd)
{
	const int width = abs((int)(m_lastFrame->GetRect().left - m_lastFrame->GetPivot().x));
	const int height = abs((int)(m_lastFrame->GetRect().top - m_lastFrame->GetPivot().y));
	FLOAT opacity = m_damaged ? 0.5f : 1.0f;
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_boundRect = dest;
	if (m_isDead)
		opacity = 0.2f;
	if (m_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(m_pos.x, m_pos.x)));
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT())->GetBitmap(), dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_lastFrame->GetRect());
	if (m_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_damaged = false;
}

void Ghost::Attacked(int damage)
{
	m_hp -= damage;
	m_HPbar->Update();
	if (m_hp <= 0)
		m_isDead = true;
}
