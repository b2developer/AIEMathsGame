#include "bsp_generator.h"

//get a pointer to the singleton
BSPGenerator* BSPGenerator::getInstance()
{
	//is defined at the start of the program
	static BSPGenerator* singleton = nullptr;

	//if the pointer contains no instance, assign one
	if (singleton == nullptr)
	{
		singleton = new BSPGenerator();
	}

	return singleton;
}

//erase each last child's region from the wall entity map
void BSPGenerator::eraseRecursive(std::vector<std::vector<WallEntity*>>& map, Container* container)
{
	//the container has a left child, check if it has children
	if (container->leftChild != nullptr)
	{
		eraseRecursive(map, container->leftChild);
	}

	//the container has a right child, check if it has children
	if (container->rightChild != nullptr)
	{
		eraseRecursive(map, container->rightChild);
	}

	//this is the last child, erase it's region from the map
	if (container->leftChild == nullptr && container->rightChild == nullptr)
	{
		container->eraseRegion(map, container->minY, container->minX, container->maxY, container->maxX);
	}
}

//erase all wall entities along a line connecting two brothers together
void BSPGenerator::connectBrothersRecursive(std::vector<std::vector<WallEntity*>>& map, Container * container)
{

	//this container contains two children ie. two brothers
	if (container->leftChild != nullptr && container->rightChild != nullptr)
	{
		connectBrothersRecursive(map, container->leftChild);
		connectBrothersRecursive(map, container->rightChild);

		//get the centre of each brother
		index2D left = container->leftChild->centre();
		index2D right = container->rightChild->centre();

		//which direction is the line in 
		if (left.i == right.i)
		{
			//horizontal line
			for (int j = left.j; j <= right.j; j++)
			{
				container->erase(map, left.i, j);
			}
		}
		else if (left.j == right.j)
		{
			//vertical line
			for (int i = left.i; i <= right.i; i++)
			{
				container->erase(map, i, left.j);
			}
		}
	}
}

void BSPGenerator::generateMap(std::vector<std::vector<WallEntity*>>& map, Path& pathMap, int recursionLevel, float clamp)
{
	size_t size1 = map.size();
	size_t size2 = map[0].size();

	Container container = Container{};

	//start from 0
	container.maxX = (int)size2 - 1;
	container.maxY = (int)size1 - 1;

	//split the container recursively
	container.split(recursionLevel, clamp);

	//generate the path
	pathMap.generateNodesRecursive(&container);

    //erase the insides of each container on the map
	eraseRecursive(map, &container);

	//erase the corridor linking every sub-container
	connectBrothersRecursive(map, &container);
}
