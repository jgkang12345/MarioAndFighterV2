#pragma once
/***********************************************
	Sprite
***********************************************/
class Sprite
{
private:
	D2D1_RECT_F		m_rect;
	D2D1_POINT_2F	m_pivotPos;
public:
	Sprite(const D2D1_RECT_F& _rect, const D2D1_POINT_2F& _pivotPos) : m_rect(_rect), m_pivotPos(_pivotPos) {};
	Sprite() {};
	virtual ~Sprite() {};

	D2D1_RECT_F		GetRect() { return m_rect; }
	D2D1_POINT_2F	GetPivot() { return m_pivotPos; }
	void			SetPivot(const D2D1_POINT_2F& _pivot) { m_pivotPos = _pivot; }
};

