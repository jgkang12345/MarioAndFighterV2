#pragma once
/*****************************************************
	GameObject: 게임에서 생명이 있는 것 최상위 클래스
*****************************************************/
class GameObject
{
protected:
	Pos			m_pos = { 0, 0 };
	Dir			m_dir = Dir::NONE;
	OBJECT_TYPE m_objType;
	int			m_hPower = 0;
	int			m_vPower = 0;
	char		m_bitmapKey[256];
	D2D1_RECT_F m_boundRect = { 0, 0, 0, 0 };
public:
	GameObject(OBJECT_TYPE _type) : m_objType(_type) {};
	virtual ~GameObject() {};
public:
	Pos	GetPos() { return m_pos; }
	Dir GetDir() { return m_dir; }
	char* GetFilePath() { return m_bitmapKey; }
	OBJECT_TYPE GetObjectType() { return m_objType; }
	int GetHPower() { return m_hPower; }
	int GetVPower() { return m_vPower; }

	void SetBitmapKey(const char* _key) { strcpy_s(m_bitmapKey, _key); }
	void SetPos(const Pos& _pos) { m_pos = _pos; }
	void SetDir(Dir _dir) { m_dir = _dir; }
	void SetObjectType(OBJECT_TYPE _type) { m_objType = _type; }
	void SetHPower(int _hPower) { m_hPower = _hPower; }
	void SetVPower(int _vPower) { m_vPower = _vPower; }
};

