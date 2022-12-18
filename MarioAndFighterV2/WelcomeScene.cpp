#include "pch.h"
#include "WelcomeScene.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "GameWnd.h"
#include "SceneManager.h"
void WelcomeScene::Update(GameWnd* _wnd)
{
	if (m_start)
	{
		SceneManager::GetInstance()->SetSceen(GAME);
		m_start = false;
	}
}

void WelcomeScene::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	Bitmap* mm = ResourceManager::GetInstance()->GetBitmap(m_bitmapKey, _wnd->GetRRT());
	RECT rect;
	GetClientRect(_wnd->GetHwnd(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };
	D2D1_RECT_F source = { 0, 0, mm->GetWidht(), mm->GetHeight() };
	_wnd->GetBRT()->DrawBitmap(mm->GetBitmap(), rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, source);
	_wnd->GetBRT()->EndDraw();
	_wnd->GetBRT()->GetBitmap(&bitmap);
	_wnd->GetRT()->BeginDraw();
	if (bitmap)
		_wnd->GetRT()->DrawBitmap(bitmap);
	_wnd->GetRT()->EndDraw();
}

void WelcomeScene::Init(GameWnd* _wnd)
{
	strcpy_s(m_bitmapKey, "welcome.png");
}

void WelcomeScene::Clean()
{

}

void WelcomeScene::KeyDownBind(WPARAM _param)
{
	m_start = true;
}

void WelcomeScene::KeyUpBind(WPARAM _wparam)
{
}
