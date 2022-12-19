#include "pch.h"
#include "ResourceManager.h"
#include "D2D1Core.h"
#include "FileUtils.h"
#include "Sprite.h"
#include "Animation.h"
#include "PlayerJumpAnimation.h"
ResourceManager* ResourceManager::m_instance = nullptr;
ResourceManager::ResourceManager()
{
	// »ý¼º
}

ResourceManager::~ResourceManager()
{
	for (auto it = m_resource.begin(); it != m_resource.end();)
		if (it->second)
			delete it->second;

	if (m_instance)
		delete m_instance;
}

ResourceManager* ResourceManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new ResourceManager();
	return m_instance;
}

Bitmap* ResourceManager::GetBitmap(char* _key, ID2D1HwndRenderTarget** _rrt)
{
	if (m_resource.find(_key) != m_resource.end())
		return m_resource.find(_key)->second;
	else
	{
		TCHAR path[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _key, strlen(_key), path, strlen(_key));
		Bitmap* ret = D2D1Core::GetInstance()->LoadBitmapByFileName(_rrt, path);
		m_resource.insert({ _key, ret });
		return ret;
	}
}

void* ResourceManager::LoadBinaryData(const char* _path)
{
	void* ret = nullptr;
	FILE* p_file = NULL;
	fopen_s(&p_file, _path, "rb");
	char exp[256];
	if (p_file != NULL)
	{
		FileUtils::GetFileExp(_path, exp);
		if (0 == strcmp(exp, "spr"))
		{
			SpriteBinaryFileHeader* header = new SpriteBinaryFileHeader();
			fread(header, sizeof(SpriteBinaryFileHeader), 1, p_file);

			if (header)
			{
				SpriteBinaryFileData* bStream = new SpriteBinaryFileData[header->spriteCount];
				fread(bStream, sizeof(SpriteBinaryFileData), header->spriteCount, p_file);

				switch (header->resourceType)
				{
				case SPRITE:
					for (int i = 0; i < header->spriteCount; i++)
					{
						bStream[i].rect.right += 1;
						bStream[i].rect.bottom += 1;
						ret = new Sprite(bStream[i].rect, bStream[i].pivotPos);
					}
					break;
				case  ANIMATION:
				{
					ret = new Animation();
					for (int i = 0; i < header->spriteCount; i++)
					{
						bStream[i].rect.right += 1;
						bStream[i].rect.bottom += 1;
						Sprite* sprite = new Sprite(bStream[i].rect, bStream[i].pivotPos);
						reinterpret_cast<Animation*>(ret)->AddClip(sprite);
					}
					break;
				}
				}
				delete[] bStream;
			}
			delete header;
		}
	}

	return ret;
}

void* ResourceManager::LoadBinaryDataPlayerJump(const char* _path)
{
	void* ret = nullptr;
	FILE* p_file = NULL;
	fopen_s(&p_file, _path, "rb");
	char exp[256];
	if (p_file != NULL)
	{
		FileUtils::GetFileExp(_path, exp);
		if (0 == strcmp(exp, "spr"))
		{
			SpriteBinaryFileHeader* header = new SpriteBinaryFileHeader();
			fread(header, sizeof(SpriteBinaryFileHeader), 1, p_file);

			if (header)
			{
				SpriteBinaryFileData* bStream = new SpriteBinaryFileData[header->spriteCount];
				fread(bStream, sizeof(SpriteBinaryFileData), header->spriteCount, p_file);

				ret = new PlayerJumpAnimation();
				for (int i = 0; i < header->spriteCount; i++)
				{
					bStream[i].rect.right += 2;
					bStream[i].rect.bottom += 2;
					Sprite* sprite = new Sprite(bStream[i].rect, bStream[i].pivotPos);
					reinterpret_cast<Animation*>(ret)->AddClip(sprite);
				}
				delete[] bStream;
			}
			delete header;
		}
	}

	return ret;
}
