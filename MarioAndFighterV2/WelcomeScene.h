#pragma once
#include "Scene.h"
#include "Bitmap.h"
class WelcomeScene : public Scene
{
private:
	Bitmap* m_bitmap;
	char	m_bitmapKey [256];
	bool	m_start = false;
public:
	WelcomeScene(GameWnd* _wnd) { Init(_wnd); };
	~WelcomeScene() {};
public:
	virtual void	Update(GameWnd* _wnd) override;
	virtual void	Render(GameWnd* _wnd) override;
	virtual void	Init(GameWnd* _wnd) override;
	virtual void	Clean() override;
	virtual void	KeyDownBind(WPARAM _param) override;
	virtual void	KeyUpBind(WPARAM _wparam) override;
};

