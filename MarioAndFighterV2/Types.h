#pragma once
/// <summary>
///  SCENE_TYPE: ��Ÿ�� 
/// </summary>
enum SCENE_TYPE : int
{
	GAME = 0,
	WELCOME = 1,
	LOADING = 2,
	ENDING = 3
};

/// <summary>
///  SpriteBinaryFileHeader: Sprite Tool ���� ���� 
///	 Binary File Load 
/// </summary>
struct SpriteBinaryFileHeader
{
	char fileName[256];
	int resourceType;
	int  spriteCount;
};

/// <summary>
///  SpriteBinaryFileData: Sprite Tool ���� ���� 
///	 Binary File Load 
/// </summary>
struct SpriteBinaryFileData
{
	D2D1_RECT_F		rect;
	D2D1_POINT_2F	pivotPos;
};

/// <summary>
///  RESOURCE_TYPE: ���ҽ� Ÿ�� ����
/// </summary>
enum RESOURCE_TYPE : int
{
	SPRITE = 0,
	ANIMATION = 1,
	EVENT = 2,
	MAP = 3,
	GAME_OBJECT = 4
};

/// <summary>
///  Pos: GameObject��ǥ
/// </summary>
struct Pos
{
	int x;
	int	y;
};

/// <summary>
///  OBJECT_TYPE: ������Ʈ ���а�
/// </summary>
enum OBJECT_TYPE
{
	PlayerObj = 100,
	NefendesObj = 200,
	GhostObj = 300,
	KumaObj = 400,
	PStandOffObj = 500,
	MStandOffObj = 600,
	GStandOffObj = 700,
	KStandOffObj = 800,
	KSStandOffObj = 900
};

/// <summary>
///  Dir: ���� ���а�
/// </summary>
enum Dir : int
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	NONE = 4
};

/// <summary>
///  Dir: ���� ���а�
/// </summary>
enum GAME_TYPE : int
{
	OVERWORLD,
	BATTLE
};

/// <summary>
///  EVENT_TYPE: Ÿ�� Ÿ��
/// </summary>
enum EVENT_TYPE : int
{
	EMPTYType = 0,
	WALLType = 1,
	PlayerType = 2,
	NefendesType = 3,
	GhostType = 4,
	KumaType = 5,
	NefendesRect = 6,
	GhostRect = 7
};

/// <summary>
///  MapDataBinaryFile: MapData ����
/// </summary>
struct MapDataBinaryFile
{
	char imgFileName[256]; // path
	char fileName[256];
	int xSize;
	int ySize;
	int mapData[256][256];
};

enum MONSTER_PATTERN : int
{
	MONSTER_IDEL,
	MONSTER_STAND_OFF_ATTACK,
	MONSTER_ATTACK,
	MONSTER_PMOVE,
	MONSTER_SPECIAL
};