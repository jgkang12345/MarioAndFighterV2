#pragma once
#include "GameObject.h"
class Animation;
class GameWnd;
class Map;
class PlayerStandOffWeapon : public GameObject
{
private:
	Animation* m_missile;
	bool m_isDead = false;
	int  m_damaged = 2;
public:
	PlayerStandOffWeapon() : GameObject(PStandOffObj) {};
	virtual ~PlayerStandOffWeapon();
public:
	void SetMissileAnimation(Animation* _ani) { m_missile = _ani; }
	Animation* GetMissileAnimation() { return m_missile; }
	void Update(Map* _map, std::vector<Map*>& _maplist);
	void Render(GameWnd* _wnd, class Player* player);
	bool IsDead() { return m_isDead; }
};

