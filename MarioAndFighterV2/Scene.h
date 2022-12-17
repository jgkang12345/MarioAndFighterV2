#pragma once
/********************************************************
	Scene : Scene ��ü�� �ֻ��� �θ� Ŭ����
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

