#include <ctime>

#include "Application2D.h"
#include "file_manager.h"

FileManager fileManager = {};

int main()
{
	//initalise the random number generator
	srand((unsigned int)time(NULL));

	//create, run and delete the app
	auto app = new Application2D();
	app->m_fileManager = &fileManager;

	app->run("MathsGame - AIE 2017", 1920, 1080, false);
	delete app;

	return 0;
}