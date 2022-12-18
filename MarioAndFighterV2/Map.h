#pragma once
class GameWnd;
class Monster;
class Player;
/*****************************************************
	Map: 게임 Map 데이터
*****************************************************/
class Map
{
private:
	int**		m_mapData;
	int			m_XSize;
	int			m_YSize;
	char		m_filePath[256];
	char		m_imgFilePath[256];
	Monster*	m_monster;
	Pos			m_playerStartPos;
public:
	Map(const char* _mapFilePath, Player* _player, GameWnd* _wnd);
	~Map();
public:
	char* GetFileName() { return m_imgFilePath; }
	int   GetXSize() { return m_XSize; }
	int   GetYSize() { return m_YSize; }
	void  Render(GameWnd* _wnd);
	Monster* GetMonster() { return m_monster; }
	EVENT_TYPE	GetTileType(const Pos& pos);
	Pos GetPlayerStartPos() { return m_playerStartPos; };
};

