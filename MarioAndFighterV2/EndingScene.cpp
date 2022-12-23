#include "pch.h"
#include "EndingScene.h"
#include "Animation.h"
#include "SceneManager.h"
#include "Bitmap.h"
#include "GameWnd.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "GameScene.h"
void EndingScene::Update(GameWnd* _wnd)
{
	if (m_restart)
	{
		SceneManager::GetInstance()->SetSceen(WELCOME);
		SceneManager::GetInstance()->GetGameScene()->Refresh();
		m_restart = false;
	}
}

void EndingScene::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	Bitmap* mm = ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT());
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

void EndingScene::Init(GameWnd* _wnd)
{
	strcpy_s(m_imgKey, "ending.png");
	ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT());
}

void EndingScene::Clean()
{

}

void EndingScene::KeyDownBind(WPARAM _param)
{
	if (_param == A)
		m_restart = true;
}

void EndingScene::KeyUpBind(WPARAM _wparam)
{
}
