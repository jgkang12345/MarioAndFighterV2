#pragma once
/********************************************************
	Scene : Scene 객체의 최상위 부모 클래스
********************************************************/
class GameWnd;
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() {  }
public:
	virtual void	Update(GameWnd* _wnd) abstract;
	virtual void	Render(GameWnd* _wnd) abstract;
	virtual void	Init(GameWnd* _wnd) abstract;
	virtual void	Clean() abstract;
	virtual void	KeyDownBind(WPARAM _param) abstract;
	virtual void	KeyUpBind(WPARAM _wparam) abstract;
};

