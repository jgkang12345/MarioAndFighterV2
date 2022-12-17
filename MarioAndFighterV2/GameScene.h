#pragma once
#include "Scene.h"
/********************************************************
	GameScene : Game의 내용을 모두 가지고 있는 클래스
********************************************************/
class Camera;
class Player;
class Map;
class GameWnd;
class GameScene : public Scene
{
private:
	std::vector<Map*>		m_map;
	Camera*					m_camera;
	Player*					m_player;
	GAME_TYPE				m_type = OVERWORLD;
public:
	GameScene(GameWnd* _wnd) { Init(_wnd); }
	GameScene(const char* _mapPath, const char* _playerPath, GameWnd* _wnd)
	{
		Init(_wnd);
	}
	~GameScene()
	{
		Clean();
	}

public:
	virtual void	Init(GameWnd* _wnd)			override;
	virtual	void	Update(GameWnd* _wnd)		override;
	virtual void	Render(GameWnd* _wnd)		override;
	virtual void	KeyDownBind(WPARAM _param)	override;
	virtual void	KeyUpBind(WPARAM _wparam)	override;
	virtual void	Clean()						override;

public:
	void SetGameType(GAME_TYPE _type) { m_type = _type; }
};

