#pragma once
#include "GameObject.h"
class Animation;
class GameWnd;
class Map;
class Player;
class NefendesStandOffWeapon : public GameObject
{
private:
	Animation* m_missile;
	bool m_isDead = false;
	int  m_damage = 3;
public:
	NefendesStandOffWeapon() : GameObject(MStandOffObj) {};
	virtual ~NefendesStandOffWeapon();
public:
	void SetMissileAnimation(Animation* _ani) { m_missile = _ani; }
	Animation* GetMissileAnimation() { return m_missile; }
	void Update(Map* _map, Player* player);
	void Render(GameWnd* _wnd, Player* player);

	bool IsDead() { return m_isDead; }
};

