#include "pch.h"
#include "FileUtils.h"
FileUtils* FileUtils::m_instance = nullptr;
FileUtils* FileUtils::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new FileUtils();
	return m_instance;
}

void FileUtils::GetFileExp(IN TCHAR* _fileName, OUT TCHAR* _ret)
{
	std::stack<TCHAR> s;
	int pathLen = _tcslen(_fileName);
	for (int i = pathLen - 1; i >= 0; i--)
	{
		if (_fileName[i] == _T('.'))
			break;
		s.push(_fileName[i]);
	}

	int index = 0;

	while (s.empty() == false)
	{
		TCHAR t = s.top();
		s.pop();
		_ret[index] = t;
		index++;
	}
	_ret[index] = '\0';
}

void FileUtils::GetFileExp(IN const char* _fileName, OUT char* _ret)
{
	std::stack<char> s;
	int pathLen = strlen(_fileName);
	for (int i = pathLen - 1; i >= 0; i--)
	{
		if (_fileName[i] == _T('.'))
			break;
		s.push(_fileName[i]);
	}

	int index = 0;

	while (s.empty() == false)
	{
		TCHAR t = s.top();
		s.pop();
		_ret[index] = t;
		index++;
	}
	_ret[index] = '\0';
}

void FileUtils::GetFileName(IN const char* _path, OUT char* _fileName)
{
	std::stack<char> s;
	int pathLen = strlen(_path);
	for (int i = pathLen - 1; i >= 0; i--)
	{
		if (_path[i] == _T('\\'))
			break;
		s.push(_path[i]);
	}

	int index = 0;

	while (s.empty() == false)
	{
		char t = s.top();
		s.pop();
		_fileName[index] = t;
		index++;
	}
	_fileName[index] = '\0';
}

void FileUtils::GetFileList(std::vector<TCHAR*>& _fileList, const TCHAR* _rootPath)
{
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFileW(_rootPath, &data);
	
	while (FindNextFileW(hFind, &data))
	{
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&  //파일이라면
			!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)) //시스템파일은 제외
		{
			TCHAR* cha = new TCHAR[256];

			for (int i = 0; i <= _tcslen(data.cFileName); i++)
				cha[i] = data.cFileName[i];
			_fileList.push_back(cha);
		}
	}
	FindClose(hFind);
}
