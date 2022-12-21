#pragma once
#include "Monster.h"
class HPBar;
class GameWnd;
class Map;
class Player;
class GhostStandOffWeapon;
class Ghost : public Monster
{
private:
	std::queue<MONSTER_PATTERN>			 m_patternQ;
	std::vector<GhostStandOffWeapon*>	 m_missiles;
	int									 m_hp = 250;
	int									 m_stand_off_damage = 20;
	int									 m_attack = 5;
	HPBar* m_HPbar = nullptr;
	bool								 m_isDead = false;
public:
	Ghost(OBJECT_TYPE _type, GameWnd* _wnd);
	~Ghost();
public:
	virtual void Init(GameWnd* _wnd) override;
	virtual void Update(Map* _map, Player* _player, GAME_TYPE _type) override;
	virtual void OVERWORLDUpdate(Map* _map, Player* _player) override;
	virtual void BATTLEUpdate(Map* _map, Player* _player) override;
	virtual void Render(GameWnd* _wnd, GAME_TYPE _type) override;
	virtual void OVERWORLDRender(GameWnd* _wnd) override;
	virtual void BATTLERender(GameWnd* _wnd) override;
	virtual void CommonRender(GameWnd* _wnd) override;
	int  GetHp() { return m_hp; }
	bool IsDead() { return m_isDead; }
	void Attacked(int damage);
	std::vector<GhostStandOffWeapon*>& GetMissiles() { return m_missiles; }
};

