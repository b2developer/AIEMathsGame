#pragma once
#include <string>
#include "Texture.h"
#include "Font.h"
#include "Audio.h"
#include "Input.h"

/*
* class FileManager
*
* stores the path to useful directories
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class FileManager
{
public:
	
	/*
	* FileManager()
	* constructor - gets the file path to the .exe folder
	*/
	FileManager();

	/*
	* ~FileManager()
	* destructor - deletes all of the resource pointers
	*/
	~FileManager();

	std::string exePath; //path to the exe folder
	std::string resourcePath; //path to the resource folder

};