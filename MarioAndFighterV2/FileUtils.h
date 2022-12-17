#pragma once
/***********************************************
	FPSManager: 파일 처리 관련 유틸 클래스
***********************************************/
class FileUtils
{
private:
	static FileUtils* m_instance;
public:
	FileUtils() {};
	~FileUtils() {};
public:
	static FileUtils* GetInstance();
	static void GetFileExp(IN TCHAR* _fileName, OUT TCHAR* _ret);
	static void GetFileExp(IN const char* _fileName, OUT char* _ret);
	static void GetFileName(IN const char* _path, OUT char* _fileName);
	static void GetFileList(std::vector<TCHAR*>& _fileList, const TCHAR* _rootPath);
};

