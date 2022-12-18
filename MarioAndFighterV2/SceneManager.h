#pragma once
/***********************************************
	SceneManager: Scene °ü¸®
***********************************************/
class Scene;
class GameWnd;
class GameScene;
class SceneManager
{
private:
	static SceneManager* m_instance;
	std::vector<Scene*>		m_scene_vector;
	SCENE_TYPE				m_type = WELCOME;
public:
	SceneManager() { };
	~SceneManager() { Clean(); };
public:
	static SceneManager* GetInstance();
	void	Init(GameWnd* _wnd);
	void	Update(GameWnd* _wnd);
	void	Render(GameWnd* _wnd);
	void	KeyDownBind(WPARAM _wparam);
	void	KeyUpBind(WPARAM _wparam);
	void	Clean();
	void	SetSceen(SCENE_TYPE _type) { m_type = _type; }
	GameScene* GetGameScene();
};