#include "file_manager.h"
#include <Windows.h>

//constructor
FileManager::FileManager()
{

	//get the path to the .exe
	char buffer[10000];
	::GetModuleFileName(NULL, buffer, sizeof(buffer) - 1);
	char *fileName = strrchr(buffer, '\\');
	*fileName = 0;
	
	//.exe folder path
	exePath = buffer;

	//resources folder path
	resourcePath = exePath + "\\resources\\";
}

//destructor
FileManager::~FileManager()
{
	
}
