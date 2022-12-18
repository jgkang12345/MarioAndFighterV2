#pragma once
/***********************************************
	ResourceManager: 府家胶 包府
***********************************************/
class Bitmap;
class ResourceManager
{
private:
	static ResourceManager* m_instance;
	std::map<char*, Bitmap*> m_resource;
public:
	ResourceManager();
	~ResourceManager();
public:
	static ResourceManager* GetInstance();
	Bitmap* GetBitmap(char* _key, ID2D1HwndRenderTarget** _rrt);
	void* LoadBinaryData(const char* _path);
	void* LoadBinaryDataPlayerJump(const char* _path);
};

