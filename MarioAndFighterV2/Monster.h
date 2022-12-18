#pragma once
#include "GameObject.h"
/*****************************************************
	Monster: 게임 Monster 데이터
*****************************************************/
class GameWnd;
class Animation;
class Map;
class Player;
class Sprite;
class Monster : public GameObject
{
protected:
	std::vector<Animation*> m_animation_vector;
	char					m_imgKey[256];
	Sprite*					m_lastFrame;
	bool					m_damaged = false;
	bool					m_isRotation = false;
public:
	Monster(OBJECT_TYPE _type, GameWnd* _wnd);
	virtual ~Monster();

public:
	virtual void Init(GameWnd* _wnd) abstract;
	virtual void Update(Map* _map, Player* _player, GAME_TYPE _type) abstract;
	virtual void OVERWORLDUpdate(Map* _map, Player* _player) abstract;
	virtual void BATTLEUpdate(Map* _map, Player* _player) abstract;
	virtual void Render(GameWnd* _wnd, GAME_TYPE _type) abstract;
	virtual void OVERWORLDRender(GameWnd* _wnd) abstract;
	virtual void BATTLERender(GameWnd* _wnd) abstract;
	virtual void CommonRender(GameWnd* _wnd) abstract;
	bool IsCrash(const D2D1_RECT_F& _rect);
	void SetImgKey(const char* _imgKey) { strcpy_s(m_imgKey, _imgKey); }
};

