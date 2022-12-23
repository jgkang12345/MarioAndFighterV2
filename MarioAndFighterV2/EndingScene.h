#pragma once
#include "Scene.h"
class Animation;
/*****************************************************
	EndingScene: ¿£µù ¾À
*****************************************************/
class EndingScene : public Scene
{
private:
	Animation* m_loadAnimation;
	int		   m_loadCount = 0;
	char	   m_imgKey[256];
	bool	   m_restart;
public:
	EndingScene(GameWnd* _wnd) { Init(_wnd); }
	~EndingScene() { Clean(); }

public:
	virtual void	Update(GameWnd* _wnd) override;
	virtual void	Render(GameWnd* _wnd) override;
	virtual void	Init(GameWnd* _wnd) override;
	virtual void	Clean() override;
	virtual void	KeyDownBind(WPARAM _param) override;
	virtual void	KeyUpBind(WPARAM _wparam) override;
};

