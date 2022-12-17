#pragma once
#include "GameObject.h"
/*****************************************************
	Player: ���� �÷��̾� Ŭ����
*****************************************************/
class Animation;
class GameWnd;
class Map;
class Sprite;
class Camera;
enum JUMP 
{
	JUMP_UP,
	JUMP_END,
	JUMP_DOWN,
	JUMP_DONE,
	JUMP_NONE
};
enum ATTACK 
{
	ATTACK_NONE = 0,
	ATTACK_START = 1,
	ATTACK_ING = 2,
	ATTACK_STAND_OFF_START = 3,
	ATTACK_STAND_OFF_ING= 4
};

class Player : public GameObject
{
private:
	std::vector<Animation*> m_animation_vector;
	char					m_imgKey [256];
	int						m_mapSeq = 0;
	JUMP					m_jump = JUMP_NONE;
	ATTACK					m_attack = ATTACK_NONE;
	Sprite*					m_lastSprite;
	bool					m_damaged = false;
	bool					m_isRotation = false;
	bool					m_isStop = true;
	Camera*					m_camera;
public:
	Player(const char* _imgKey, const char* _bitmapKey);
	virtual ~Player();

public:
	void Init();
	void Update(Map* _map, GAME_TYPE _type, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void OVERWORLDUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void BATTLEUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void Render(GameWnd* _wnd, GAME_TYPE _type);
	void OVERWORLDRender(GameWnd* _wnd);
	void BATTLERender(GameWnd* _wnd);
	void CommonRender(GameWnd* _wnd, Sprite* _sprite, bool _isRotation, char* _key);
	void KeyUpBind(WPARAM _wparam, GAME_TYPE _type);
	void KeyDownBind(WPARAM _wparam, GAME_TYPE _type);
	void SetAnimation(Animation* m_animation);
	void SetImgKey(const char* _imgKey) { strcpy_s(m_imgKey, _imgKey); }
	int  GetMapInedx() { return m_mapSeq; }
	bool IsCrash(const D2D1_RECT_F& _rect);
};
