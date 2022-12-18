#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "LoadScene.h"
#include "WelcomeScene.h"
SceneManager* SceneManager::m_instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new SceneManager();
	return m_instance;
}

void SceneManager::Init(GameWnd* _wnd)
{
	m_scene_vector.resize(SCENE_COUNT);
	m_scene_vector[SCENE_TYPE::GAME] = new GameScene(_wnd);
	m_scene_vector[SCENE_TYPE::LOADING] = new LoadScene(_wnd);
	m_scene_vector[SCENE_TYPE::WELCOME] = new WelcomeScene(_wnd);
}

void SceneManager::Update(GameWnd* _wnd)
{
	m_scene_vector[m_type]->Update(_wnd);
}

void SceneManager::Render(GameWnd* _wnd)
{
	 m_scene_vector[m_type]->Render(_wnd);
}


void SceneManager::KeyDownBind(WPARAM _wparam)
{
	if (m_type == WELCOME)
		m_scene_vector[m_type]->KeyDownBind(_wparam);

	if (m_type == GAME)
		m_scene_vector[m_type]->KeyDownBind(_wparam);
}

void SceneManager::KeyUpBind(WPARAM _wparam)
{
	if (m_type == GAME)
		m_scene_vector[m_type]->KeyUpBind(_wparam);
}

void SceneManager::Clean()
{
	for (auto& scene : m_scene_vector)
		if (scene)
			delete scene;

	if (m_instance)
		delete m_instance;
}

GameScene* SceneManager::GetGameScene() 
{
	return reinterpret_cast<GameScene*>(m_scene_vector[GAME]);
}