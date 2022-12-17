#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Map.h"
#include "GameWnd.h"
#include "Monster.h"
#include "Camera.h"
#include "NefendesStandOffWeapon.h"
#include "Nefendes.h"
mapSqList

void GameScene::Init(GameWnd* _wnd)
{
	m_map.resize(MAP_COUNT);
	m_player = new Player("overworld_mario.png", "battleMario.png");
	m_map[m_player->GetMapInedx()] = new Map(mapSq[m_player->GetMapInedx()], m_player, _wnd);
	m_camera = new Camera(m_player->GetPos().x, m_player->GetPos().y, *m_map.begin());
}

void GameScene::Update(GameWnd* _wnd)
{
	m_player->Update(m_map[m_player->GetMapInedx()], m_type, m_map, _wnd);
	Monster* monster = m_map[m_player->GetMapInedx()]->GetMonster();
	monster->Update(m_map[m_player->GetMapInedx()], m_player, m_type);
	m_camera->Update(m_player,m_map[m_player->GetMapInedx()],m_type);
}

void GameScene::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	std::vector<GameObject*> object_vector;
	const int mapIndex = m_player->GetMapInedx();
	Monster* monster = m_map[mapIndex]->GetMonster();
	object_vector.push_back(monster);
	object_vector.push_back(m_player);
	object_vector.insert(std::end(object_vector), reinterpret_cast<Nefendes*>(monster)->GetMissiles().begin(), reinterpret_cast<Nefendes*>(monster)->GetMissiles().end());
	sort(object_vector.begin(), object_vector.end(), [](GameObject* _left, GameObject* _right)
		{
			if (_left->GetPos().y != _right->GetPos().y)
				return _left->GetPos().y < _right->GetPos().y;
			else
				return _left->GetPos().x < _right->GetPos().x;
		});
	m_map[mapIndex]->Render(_wnd);
	for (auto& item : object_vector)
	{
		if (item->GetObjectType() == PlayerObj)
			reinterpret_cast<Player*>(item)->Render(_wnd, m_type);
		else if (item->GetObjectType() == MStandOffObj)
			reinterpret_cast<NefendesStandOffWeapon*>(item)->Render(_wnd, m_player);
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
	_wnd->GetRT()->EndDraw();
}

void GameScene::KeyDownBind(WPARAM _param)
{
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
		delete m_player;
}
