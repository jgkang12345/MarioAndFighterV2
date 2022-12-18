#pragma once
class GameObject;
class GameWnd;
class HPBar
{
private:
	GameObject* m_object;
	D2D1_RECT_F m_hpMaxRect;
	D2D1_RECT_F m_hpRect;
	int m_maxHP;
	int m_hp;
	int m_ca;
public:
	HPBar(GameObject* object);
	void Render(GameWnd* _wnd);
	void Update();
};

