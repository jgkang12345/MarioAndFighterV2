#include "pch.h"
#include "Map.h"
#include "FileUtils.h"
#include "Monster.h"
#include "Player.h"
#include "GameWnd.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "D2D1Core.h"
#include "Nefendes.h"
Map::Map(const char* _mapFilePath, Player* _player, GameWnd* _wnd)
{
	FILE* p_file = NULL;
	MapDataBinaryFile* file = new MapDataBinaryFile;
	fopen_s(&p_file, _mapFilePath, "rb");
	if (p_file != NULL)
		fread(file, sizeof(MapDataBinaryFile), 1, p_file);
	if (file)
	{
		FileUtils::GetFileName((*file).fileName, m_filePath);
		FileUtils::GetFileName((*file).imgFileName, m_imgFilePath);
		m_XSize = (*file).xSize;
		m_YSize = (*file).ySize;

		m_mapData = new int* [(*file).ySize];
		for (int y = 0; y < (*file).ySize; y++)
		{
			m_mapData[y] = new int[(*file).xSize];
			memset(m_mapData[y], 0, (*file).xSize * 4);
		}

		for (int y = 0; y < m_YSize; y++)
		{
			for (int x = 0; x < m_XSize; x++)
			{
				m_mapData[y][x] = (*file).mapData[y][x];
				switch (m_mapData[y][x])
				{
				case EVENT_TYPE::PlayerType:
					_player->SetPos({ ((((x + 1) * TILESIZE) - (x * TILESIZE)) / 2) + (x * TILESIZE), y * TILESIZE + TILESIZE } );
					break;

				case EVENT_TYPE::NefendesType:
					m_monster = new Nefendes(NefendesObj, _wnd);
					m_monster->SetPos({ ((((x + 1) * TILESIZE) - (x * TILESIZE)) / 2) + (x * TILESIZE), y * TILESIZE + TILESIZE });
					break;

				case EVENT_TYPE::GhostType:
					// m_monster = new Monster(GhostObj, _wnd);
					// m_monster->SetPos({ ((((x + 1) * TILESIZE) - (x * TILESIZE)) / 2) + (x * TILESIZE), y * TILESIZE + TILESIZE });
					break;

				case EVENT_TYPE::KumaType:
					// m_monster = new Monster(KumaObj, _wnd);
					// m_monster->SetPos({ ((((x + 1) * TILESIZE) - (x * TILESIZE)) / 2) + (x * TILESIZE), y * TILESIZE + TILESIZE });
					break;
				default:
					break;
				}
			}
		}
	}
	delete file;
}

Map::~Map()
{
	for (int y = 0; y < m_YSize; y++) 
		if (m_mapData[y])
			delete[] m_mapData[y];
	if (m_mapData)
		delete[] m_mapData;
	m_mapData = nullptr;
	if (m_monster)
		delete m_monster;
	m_monster = nullptr;
}

void Map::Render(GameWnd* _wnd)
{
	_wnd->GetBRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(m_imgFilePath, _wnd->GetRRT())->GetBitmap());
}

EVENT_TYPE Map::GetTileType(const Pos& pos)
{
	int x = pos.x / TILESIZE;
	int y;

	char target[] = "battle";
	if (NULL != strstr(GetFileName(), target))
	{
		y = (pos.y / TILESIZE) - 1;
	}
	else
	{
		y = (pos.y / TILESIZE);
	}

	if (y < 0 || x < 0 || x >= m_XSize || y >= m_YSize || pos.x < 0 || pos.y < 0)
		return EVENT_TYPE::WALLType;

	return (EVENT_TYPE)m_mapData[y][x];
}
