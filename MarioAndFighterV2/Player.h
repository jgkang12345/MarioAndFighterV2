#pragma once
#include "GameObject.h"
/*****************************************************
	Player: 게임 플레이어 클래스
*****************************************************/
class Animation;
class GameWnd;
class Map;
class Sprite;
class Camera;
class PlayerStandOffWeapon;
class HPBar;
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
	std::vector<Animation*>				m_animation_vector;
	char								m_imgKey [256];
	int									m_mapSeq = 0;
	JUMP								m_jump = JUMP_NONE;
	ATTACK								m_attack = ATTACK_NONE;
	Sprite*								m_lastSprite;
	bool								m_damaged = false;
	bool								m_isRotation = false;
	bool								m_isStop = true;
	Camera*								m_camera;
	std::vector<PlayerStandOffWeapon*>  m_missiles;
	int									m_hp = 150;
	int									m_stand_off_damage = 2;
	int									m_damage = 10;
	HPBar*								m_HPbar = nullptr;
	bool								m_isDead = false;
	bool								m_isDeadRender = false;
	bool								m_isWin = false;
	int									m_renderCnt = 0;
	bool								m_mapNext = false;

public:
	Player(const char* _imgKey, const char* _bitmapKey);
	virtual ~Player();

public:
	void Init();
	void Update(Map* _map, GAME_TYPE _type, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void OVERWORLDUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void BATTLEUpdate(Map* _map, std::vector<Map*>& _mapLIst, GameWnd* _wnd);
	void Render(GameWnd* _wnd, Map* _map, GAME_TYPE _type);
	void OVERWORLDRender(GameWnd* _wnd, Map* _map);
	void BATTLERender(GameWnd* _wnd, Map* _map);
	void CommonRender(GameWnd* _wnd, Sprite* _sprite, bool _isRotation, char* _key);
	void KeyUpBind(WPARAM _wparam, GAME_TYPE _type);
	void KeyDownBind(WPARAM _wparam, GAME_TYPE _type);
	void SetAnimation(Animation* m_animation);
	void SetImgKey(const char* _imgKey) { strcpy_s(m_imgKey, _imgKey); }
	int  GetMapInedx() { return m_mapSeq; }
	bool IsCrash(const D2D1_RECT_F& _rect);
	std::vector<PlayerStandOffWeapon*>& GetMissiles() { return m_missiles; }
	int  GetHp() { return m_hp; }
	void Attacked(int damage);
	Sprite* GetLastSprite() { return m_lastSprite; }
	void Dead();
	bool IsDead() { return m_isDead; };
	void HPInit() { m_hp = 150;}
	void SetInit();
	bool IsRenderDead() { return m_isDeadRender; }
	bool IsWin() { return m_isWin; }
	void SetIsWin() { m_isWin = true; }
};

