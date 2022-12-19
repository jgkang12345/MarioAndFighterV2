#include "pch.h"
#include "Nefendes.h"
#include "ResourceManager.h"
#include "GameWnd.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "Animation.h"
#include "NefendesStandOffWeapon.h"
#include "HPBar.h"
const MONSTER_PATTERN pattern1[] =
{ MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL , MONSTER_IDEL };

const MONSTER_PATTERN pattern2[] =
{ MONSTER_STAND_OFF_ATTACK, MONSTER_STAND_OFF_ATTACK, MONSTER_IDEL, MONSTER_STAND_OFF_ATTACK, MONSTER_IDEL, MONSTER_STAND_OFF_ATTACK , MONSTER_IDEL };

const MONSTER_PATTERN pattern3[] =
{ MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL, MONSTER_IDEL , MONSTER_IDEL };

enum NefendesSpecifiFrame 
{
	ATTACK_FRAME = 11
};

enum NEFENDES_ANIMATION_TYPE : int
{
	NEFENDES_OVERWORLD_IDLE = 0
};

Nefendes::Nefendes(OBJECT_TYPE _type, GameWnd* _wnd) : Monster(_type, _wnd)
{
	Init(_wnd);
}

Nefendes::~Nefendes()
{
	for (auto& item : m_missiles)
		if (item)
			delete item;

	m_missiles.clear();
}

void Nefendes::Init(GameWnd* _wnd)
{
	SetImgKey("NefendesObj.png");
	m_animation_vector.resize(NEFENDES_ANIMATION_COUNT);
	m_animation_vector[NEFENDES_OVERWORLD_IDLE] = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("NeftendesAnimation.spr"));
	m_lastFrame = m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetFirst();
	ResourceManager::GetInstance()->GetBitmap(GetFilePath(), _wnd->GetRRT());
}

void Nefendes::Update(Map* _map, Player* _player, GAME_TYPE _type)
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

void Nefendes::OVERWORLDUpdate(Map* _map, Player* _player)
{

}

void Nefendes::BATTLEUpdate(Map* _map, Player* _player)
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

void Nefendes::Render(GameWnd* _wnd, GAME_TYPE _type)
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

void Nefendes::OVERWORLDRender(GameWnd* _wnd)
{
	m_lastFrame = m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetFrame();
	CommonRender(_wnd);
}

void Nefendes::BATTLERender(GameWnd* _wnd)
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
		m_lastFrame = m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetFirst();
		m_patternQ.pop();
		break;

	case MONSTER_STAND_OFF_ATTACK:
		m_lastFrame = m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetFrameNoAuto();

		if (m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetNowFrame() == ATTACK_FRAME)
		{
			const int height = m_lastFrame->GetRect().bottom - m_lastFrame->GetRect().top;
			NefendesStandOffWeapon* missile = new NefendesStandOffWeapon();
			missile->SetPos({ m_pos.x, (m_pos.y + (m_pos.y - height)) / 2 + 5 });
			if (m_isRotation)
				missile->SetHPower(5);
			else
				missile->SetHPower(-5);
			Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("missile.spr"));
			missile->SetMissileAnimation(missileAnimation);
			m_missiles.push_back(missile);
		}
		if (m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetNowFrame() == m_animation_vector[NEFENDES_OVERWORLD_IDLE]->GetFrameCount())
		{
			m_animation_vector[NEFENDES_OVERWORLD_IDLE]->Init();
			m_patternQ.pop();
		}
		break;
	}

	if (m_HPbar)
		m_HPbar->Render(_wnd);

	CommonRender(_wnd);
}

void Nefendes::CommonRender(GameWnd* _wnd)
{
	const int width = abs((int)(m_lastFrame->GetRect().left - m_lastFrame->GetPivot().x));
	const int height = abs((int)(m_lastFrame->GetRect().top - m_lastFrame->GetPivot().y));
	FLOAT opacity = m_damaged ? 0.5f : 1.0f;
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_boundRect = dest;
	if (m_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(m_pos.x, m_pos.x)));
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT())->GetBitmap(), dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_lastFrame->GetRect());
	if (m_isRotation)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_damaged = false;
}

void Nefendes::Attacked(int damage)
{
	m_hp -= damage;
	m_HPbar->Update();
}
