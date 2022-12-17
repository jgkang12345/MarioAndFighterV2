#pragma once
#include "Scene.h"
class Animation;
/*****************************************************
	LoadScene: 맵이 이동될때 마다 로딩하는 씬
*****************************************************/
class LoadScene : public Scene
{
private:
	Animation* m_loadAnimation;
	int		   m_loadCount = 0;
	char	   m_imgKey[256];

public:
	LoadScene(GameWnd* _wnd) { Init(_wnd); }
	~LoadScene() { Clean(); }

public:
	virtual void	Update(GameWnd* _wnd) override;
	virtual void	Render(GameWnd* _wnd) override;
	virtual void	Init(GameWnd* _wnd) override;
	virtual void	Clean() override;
	virtual void	KeyDownBind(WPARAM _param) override;
	virtual void	KeyUpBind(WPARAM _wparam) override;
};

