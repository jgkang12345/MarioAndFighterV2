#pragma once
#include "GameObject.h"
class Animation;
class GameWnd;
class Map;
class Player;
class Monster;
class KumaSpecalWeapon : public GameObject
{
private:
	Animation* m_missile;
	Monster* m_monster;
	bool m_isDead = false;
	int  m_damage = 10;
public:
	KumaSpecalWeapon(Monster* _monster) : GameObject(KSStandOffObj), m_monster(_monster) {};
	virtual ~KumaSpecalWeapon();
public:
	void SetMissileAnimation(Animation* _ani) { m_missile = _ani; }
	Animation* GetMissileAnimation() { return m_missile; }
	void Update(Map* _map, Player* player);
	void Render(GameWnd* _wnd, Player* player);

	bool IsDead() { return m_isDead; }
};

