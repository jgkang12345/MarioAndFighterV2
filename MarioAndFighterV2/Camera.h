#pragma once
/*****************************************************
	Camera: 게임 카메라
*****************************************************/
class Camera
{
private:
	D2D1_RECT_F m_cameraRect;
public:
	Camera(const int& _x, const int& _y, class Map* _map) { Init(_x, _y, _map); };
	~Camera();
public:
	void Init(const int& _x, const int& _y, class Map* _map);
	void Update(class Player* _player, class Map* _map, GAME_TYPE _type);
	D2D1_RECT_F GetCameraRect() { return m_cameraRect; }
	void SetCameraRect(const D2D1_RECT_F& _rect) { m_cameraRect = _rect; }
	bool IsCrash(class  Player* _player, class Map* _map);
};

