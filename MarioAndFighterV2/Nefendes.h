#pragma once
#include "Monster.h"
class NefendesStandOffWeapon;
class HPBar;
class Nefendes : public Monster
{
private:
	std::queue<MONSTER_PATTERN>			 m_patternQ;
	std::vector<NefendesStandOffWeapon*> m_missiles;
	int									 m_hp = 200;
	int									 m_stand_off_damage = 10;
	HPBar*								 m_HPbar = nullptr;
public:
	Nefendes(OBJECT_TYPE _type, GameWnd* _wnd);
	~Nefendes();
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
	void Attacked(int damage);
	std::vector<NefendesStandOffWeapon*>& GetMissiles() { return m_missiles; }
};

