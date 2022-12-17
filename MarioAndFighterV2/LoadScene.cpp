#include "pch.h"
#include "LoadScene.h"
#include "Animation.h"
#include "SceneManager.h"
#include "Bitmap.h"
#include "GameWnd.h"
#include "Sprite.h"
#include "ResourceManager.h"

void LoadScene::Init(GameWnd* _wnd)
{
	strcpy_s(m_imgKey, "star.png");
	m_loadAnimation = reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData("star.spr"));
	ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT());
}

void LoadScene::Update(GameWnd* _wnd)
{
	if (m_loadAnimation->GetNowFrame() == m_loadAnimation->GetFrameCount())
	{
		SceneManager::GetInstance()->SetSceen(GAME);
		m_loadAnimation->Init();
	}
}

void LoadScene::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	Sprite* frame = m_loadAnimation->GetFrameNoAuto();

	RECT rect;
	GetClientRect(_wnd->GetHwnd(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };
	const int width = abs((int)(frame->GetRect().left - frame->GetPivot().x));
	const int height = abs((int)(frame->GetRect().top - frame->GetPivot().y));
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(m_imgKey, _wnd->GetRRT())->GetBitmap(), rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame->GetRect());
	_wnd->GetBRT()->EndDraw();
	_wnd->GetBRT()->GetBitmap(&bitmap);
	_wnd->GetRT()->BeginDraw();

	if (bitmap)
		_wnd->GetRT()->DrawBitmap(bitmap);
	_wnd->GetRT()->EndDraw();
}

void LoadScene::Clean()
{
}

void LoadScene::KeyDownBind(WPARAM _param)
{
}

void LoadScene::KeyUpBind(WPARAM _wparam)
{
}
