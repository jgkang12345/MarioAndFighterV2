#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Map.h"
#include "GameWnd.h"
#include "Monster.h"
#include "Camera.h"
#include "NefendesStandOffWeapon.h"
#include "Nefendes.h"
#include "PlayerStandOffWeapon.h"
#include "SceneManager.h"
#include "GhostStandOffWeapon.h"
#include "Ghost.h"
mapSqList

void GameScene::Init(GameWnd* _wnd)
{
	m_map.resize(MAP_COUNT, nullptr);
	m_player = new Player("overworld_mario.png", "battleMario.png");
	m_map[m_player->GetMapInedx()] = new Map(mapSq[m_player->GetMapInedx()], m_player, _wnd);
	m_camera = new Camera(m_player->GetPos().x, m_player->GetPos().y, *m_map.begin());
	m_type = OVERWORLD;
}

void GameScene::Update(GameWnd* _wnd)
{
	if (!m_player->IsRenderDead() && !m_player->IsDead() )
		m_player->Update(m_map[m_player->GetMapInedx()], m_type, m_map, _wnd);
	Monster* monster = m_map[m_player->GetMapInedx()]->GetMonster();
	switch (monster->GetObjectType())
	{
	case NefendesObj:
		if (reinterpret_cast<Nefendes*>(monster)->IsDead())
			m_player->SetIsWin();
		break;

	case GhostObj:
		if (reinterpret_cast<Ghost*>(monster)->IsDead())
			m_player->SetIsWin();
		break;
	}

	monster->Update(m_map[m_player->GetMapInedx()], m_player, m_type);
	m_camera->Update(m_player,m_map[m_player->GetMapInedx()],m_type);
}

void GameScene::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	std::vector<GameObject*> object_vector;
	Monster* monster = m_map[m_player->GetMapInedx()]->GetMonster();
	object_vector.push_back(monster);
	object_vector.push_back(m_player);

	switch (monster->GetObjectType())
	{
	case NefendesObj:
		object_vector.insert(std::end(object_vector), reinterpret_cast<Nefendes*>(monster)->GetMissiles().begin(), reinterpret_cast<Nefendes*>(monster)->GetMissiles().end());
		break;
		
	case GhostObj:
		object_vector.insert(std::end(object_vector), reinterpret_cast<Ghost*>(monster)->GetMissiles().begin(), reinterpret_cast<Ghost*>(monster)->GetMissiles().end());
		break;
	}

	object_vector.insert(std::end(object_vector), m_player->GetMissiles().begin(), m_player->GetMissiles().end());
	sort(object_vector.begin(), object_vector.end(), [](GameObject* _left, GameObject* _right)
		{
			if (_left->GetPos().y != _right->GetPos().y)
				return _left->GetPos().y < _right->GetPos().y;
			else
				return _left->GetPos().x < _right->GetPos().x;
		});
	m_map[m_player->GetMapInedx()]->Render(_wnd);
	for (auto& item : object_vector)
	{
		if (item->GetObjectType() == PlayerObj)
			reinterpret_cast<Player*>(item)->Render(_wnd, m_map[m_player->GetMapInedx()], m_type);
		else if (item->GetObjectType() == MStandOffObj)
			reinterpret_cast<NefendesStandOffWeapon*>(item)->Render(_wnd, m_player);
		else if (item->GetObjectType() == PStandOffObj)
			reinterpret_cast<PlayerStandOffWeapon*>(item)->Render(_wnd, m_player);
		else if (item->GetObjectType() == GStandOffObj)
			reinterpret_cast<GhostStandOffWeapon*>(item)->Render(_wnd, m_player);
		else
			reinterpret_cast<Monster*>(item)->Render(_wnd, m_type);
	}
	_wnd->GetBRT()->EndDraw();
	_wnd->GetBRT()->GetBitmap(&bitmap);
	_wnd->GetRT()->BeginDraw();

	RECT rect;
	GetClientRect(_wnd->GetHwnd(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };
	if (bitmap)
		_wnd->GetRT()->DrawBitmap(bitmap, rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_camera->GetCameraRect());
		//_wnd->GetRT()->DrawBitmap(bitmap, rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_camera->GetCameraRect());
	_wnd->GetRT()->EndDraw();
}

void GameScene::KeyDownBind(WPARAM _param)
{
	if (m_player->IsRenderDead() == false && m_player->IsWin() == false)
		m_player->KeyDownBind(_param, m_type);
}

void GameScene::KeyUpBind(WPARAM _param)
{
	m_player->KeyUpBind(_param, m_type);
}

void GameScene::Clean()
{
	for (auto& item : m_map)
		if (item)
			delete item;
	m_map.clear();

	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
}

void GameScene::Refresh()
{
	m_player->SetPos(m_map[m_player->GetMapInedx()]->GetPlayerStartPos());
	m_player->SetInit();
	// m_map[m_player->GetMapInedx()]->GetMonster();
	m_camera->Init(m_player->GetPos().x, m_player->GetPos().y, m_map[m_player->GetMapInedx()]);
	m_type = OVERWORLD;
	SceneManager::GetInstance()->SetSceen(WELCOME);
}
