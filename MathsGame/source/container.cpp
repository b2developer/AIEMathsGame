#include "container.h"

//destructor
Container::~Container()
{
	//delete the children only if they exist
	if (leftChild != nullptr)
	{
		delete leftChild;
	}

	if (rightChild != nullptr)
	{
		delete rightChild;
	}
}

//create two sub-containers
void Container::split(int recursionlevel, float clamp)
{
	float halfClamp = (1 - clamp) * 0.5f;
	float startClamp = halfClamp;

	//generate random number between 0 and 1
	float rn = (rand() % 100) / 100.0f;

	if (splitDirection == Direction::Null)
	{
		int r = rand() % 2 + 1;

		//pick a random starting direction
		splitDirection = (Direction)r;
	}

	//split the container along the direction
	if (splitDirection == Direction::X)
	{
		//mid ratio
		float mid = startClamp + rn * clamp;
		int midPoint = minX + (int)floorf((maxX - minX) * mid);

		//make the new containers
		leftChild = new Container{};
		rightChild = new Container{};

		//left child
		leftChild->minX = minX;
		leftChild->maxX = midPoint;
		leftChild->minY = minY;
		leftChild->maxY = maxY;

		//right child
		rightChild->minX = midPoint;
		rightChild->maxX = maxX;
		rightChild->minY = minY;
		rightChild->maxY = maxY;

		//flip the direction
		leftChild->splitDirection = Direction::Y;
		rightChild->splitDirection = Direction::Y;
	}
	else if (splitDirection == Direction::Y)
	{
		//mid ratio
		float mid = startClamp + rn * clamp;
		int midPoint = minY + (int)floorf((maxY - minY) * mid);

		//make the new containers
		leftChild = new Container{};
		rightChild = new Container{};

		//left child
		leftChild->minX = minX;
		leftChild->maxX = maxX;
		leftChild->minY = minY;
		leftChild->maxY = midPoint;

		//right child
		rightChild->minX = minX;
		rightChild->maxX = maxX;
		rightChild->minY = midPoint;
		rightChild->maxY = maxY;
		
		//flip the direction
		leftChild->splitDirection = Direction::X;
		rightChild->splitDirection = Direction::X;
	}

	if (recursionlevel <= 1)
	{
		return;
	}

	//split the children
	leftChild->split(recursionlevel - 1, clamp);
	rightChild->split(recursionlevel - 1, clamp);
}

//get the centre of the container
index2D Container::centre()
{
	//get the sum of the min and max
	float cX = (float)(minX + maxX);
	float cY = (float)(minY + maxY);

	//get the average
	int i_cX = (int)floorf(cX / 2.0f);
	int i_cY = (int)floorf(cY / 2.0f);

	return index2D{ i_cY, i_cX };
}

//erase the wall entity from the 2D array
void Container::erase(std::vector<std::vector<WallEntity*>>& wall2D, int i, int j)
{
	//get the size of the first dimension
	int columnSize = (int)wall2D.size();

	//within the first dimension span
	if (i >= 0 && i < columnSize)
	{
		//get the size of the second dimension
		int rowSize = (int)wall2D[i].size();

		//within the second dimension span
		if (j >= 0 && j < rowSize)
		{
			delete wall2D[i][j];

			//erase the wall
			wall2D[i][j] = nullptr;
		}
	}
}

//erase a region of wall entities from the 2D array
void Container::eraseRegion(std::vector<std::vector<WallEntity*>>& wall2D, int minI, int minJ, int maxI, int maxJ)
{
	//iterate through the 2D array backwards, this stops the indices from changing when deleting parts of the array
	for (int i = maxI - 1; i > minI; i--)
	{
		for (int j = maxJ - 1; j > minJ; j--)
		{
			erase(wall2D, i, j);
		}
	}
}
