#include "pch.h"
#include "Kuma.h"
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
#include "KumaSpecalWeapon.h"
#include "KumaStandOffWeapon.h"
enum KUMA_ANIMATION_TYPE : int
{
	KUMA_OVERWORLD_IDLE = 0,
	KUMA_BATTLE_MOVE=  1,
	KUMA_BATTLE_ATTACK = 2,
	KUMA_BATTLE_STAND_OFF_ATTACK = 3,
	KUMA_BATTLE_SPECAL_ATTACK = 4,
	KUMA_BATTLE_STAND_OFF_ATTACK_MONTION = 5
};

const MONSTER_PATTERN pattern1[] =
{ MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_PMOVE, MONSTER_ATTACK, MONSTER_PMOVE , MONSTER_ATTACK };

const MONSTER_PATTERN pattern2[] =
{ MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_PMOVE, MONSTER_ATTACK, MONSTER_STAND_OFF_ATTACK , MONSTER_STAND_OFF_ATTACK };

const MONSTER_PATTERN pattern3[] =
{ MONSTER_IDEL, MONSTER_STAND_OFF_ATTACK, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL , MONSTER_SPECIAL, MONSTER_SPECIAL };


Kuma::Kuma(OBJECT_TYPE _type, GameWnd* _wnd) : Monster(_type, _wnd)
{
	Init(_wnd);
}

Kuma::~Kuma()
{
	for (auto& item : m_missiles)
		if (item)
			delete item;

	m_missiles.clear();
}

void Kuma::Init(GameWnd* _wnd)
{
	SetImgKey("Kuma.png");
	m_animation_vector.resize(KUMA_ANIMATION_COUNT);
	m_animation_vector[KUMA_OVERWORLD_IDLE] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaIdel.spr"));
	m_animation_vector[KUMA_BATTLE_MOVE] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaMove.spr"));
	m_animation_vector[KUMA_BATTLE_ATTACK] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaFlaret.spr"));
	m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaStandOffAttackMotion.spr"));
	m_lastFrame = m_animation_vector[KUMA_OVERWORLD_IDLE]->GetFirst();
	ResourceManager::GetInstance()->GetBitmap(GetFilePath(), _wnd->GetRRT());
}

void Kuma::Update(Map* _map, Player* _player, GAME_TYPE _type)
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

void Kuma::OVERWORLDUpdate(Map* _map, Player* _player)
{
}

void Kuma::BATTLEUpdate(Map* _map, Player* _player)
{
	if (!m_isDead)
	{
		if (m_HPbar == nullptr)
			m_HPbar = new HPBar(this);

		if (m_patternQ.empty() == false)
		{
			for (auto it = begin(m_missiles); it != end(m_missiles);)
			{
				if ((*it)->GetObjectType() == KStandOffObj)
				{
					if (reinterpret_cast<KumaStandOffWeapon*> (*it)->IsDead())
					{
						delete* it;
						it = m_missiles.erase(it);
					}
					else
					{
						reinterpret_cast<KumaStandOffWeapon*> (*it)->Update(_map, _player);
						it++;
					}
				}
				else
				{
					if (reinterpret_cast<KumaSpecalWeapon*> (*it)->IsDead())
					{
						delete* it;
						it = m_missiles.erase(it);
					}
					else
					{
						reinterpret_cast<KumaSpecalWeapon*> (*it)->Update(_map, _player);
						it++;
					}
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

void Kuma::Render(GameWnd* _wnd, GAME_TYPE _type)
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

void Kuma::OVERWORLDRender(GameWnd* _wnd)
{
	m_lastFrame = m_animation_vector[KUMA_OVERWORLD_IDLE]->GetFrame();
	CommonRender(_wnd);
}

void Kuma::BATTLERender(GameWnd* _wnd)
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
			m_lastFrame = m_animation_vector[KUMA_OVERWORLD_IDLE]->GetFirst();
			m_patternQ.pop();
			break;

		case MONSTER_STAND_OFF_ATTACK:
			m_lastFrame = m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetFrameNoAuto();

			if (m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == 14)
			{
				const int height = m_lastFrame->GetRect().bottom - m_lastFrame->GetRect().top;
				KumaStandOffWeapon* missile = new KumaStandOffWeapon(this);
				missile->SetPos({ m_pos.x,m_pos.y - 5 });
				if (m_isRotation)
					missile->SetHPower(5);
				else
					missile->SetHPower(-5);
				Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaStandOffAttack.spr"));
				missile->SetMissileAnimation(missileAnimation);
				m_missiles.push_back(missile);

				m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->Init();
				m_patternQ.pop();
			}
			break;

		case MONSTER_PMOVE:
		{
			m_lastFrame = m_animation_vector[KUMA_BATTLE_MOVE]->GetFrameNoAuto();

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

			int move = 4;
			m_pos.x += move * dir;

			if (m_animation_vector[KUMA_BATTLE_MOVE]->GetNowFrame() == m_animation_vector[KUMA_BATTLE_MOVE]->GetFrameCount())
			{
				m_animation_vector[KUMA_BATTLE_MOVE]->Init();
				m_patternQ.pop();
			}
			break;
		}


		case MONSTER_ATTACK:
		{
			m_lastFrame = m_animation_vector[KUMA_BATTLE_ATTACK]->GetFrameNoAuto();

			if (m_animation_vector[KUMA_BATTLE_ATTACK]->GetNowFrame() == 21)
			{
				if (SceneManager::GetInstance()->GetGameScene()->GetPlayer()->IsCrash(m_boundRect))
				{
					SceneManager::GetInstance()->GetGameScene()->GetPlayer()->Attacked(m_attack);
				}
			}

			if (m_animation_vector[KUMA_BATTLE_ATTACK]->GetNowFrame() == m_animation_vector[KUMA_BATTLE_ATTACK]->GetFrameCount())
			{
				m_animation_vector[KUMA_BATTLE_ATTACK]->Init();
				m_patternQ.pop();
			}
			break;
		}

		case MONSTER_SPECIAL:
			m_lastFrame = m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetFrameNoAuto();
			
			if (m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == 14 
				|| m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == 15 
				|| m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == 16 
				|| m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == 17)
			{
				const int height = m_lastFrame->GetRect().bottom - m_lastFrame->GetRect().top;
				KumaSpecalWeapon* missile = new KumaSpecalWeapon(this);
				missile->SetPos({ m_pos.x,m_pos.y - 10 });
				if (m_isRotation)
					missile->SetHPower(7);
				else
					missile->SetHPower(-7);
				Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("kumaSpecalAttack.spr"));
				missile->SetMissileAnimation(missileAnimation);
				m_missiles.push_back(missile);
			}

			if (m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetNowFrame() == m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->GetFrameCount())
			{
				m_animation_vector[KUMA_BATTLE_STAND_OFF_ATTACK_MONTION]->Init();
				m_patternQ.pop();
			}
			break;
		
		}

		if (m_HPbar)
			m_HPbar->Render(_wnd);
	}

	CommonRender(_wnd);
}

void Kuma::CommonRender(GameWnd* _wnd)
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

void Kuma::Attacked(int damage)
{
	m_hp -= damage;
	m_HPbar->Update();
	if (m_hp <= 0)
		m_isDead = true;
}
