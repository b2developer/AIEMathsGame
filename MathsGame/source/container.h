#pragma once
#include <vector>
#include "wall_entity.h"
#include "partition.h"

//defines X and Y as directions
enum Direction
{
	Null,
	X,
	Y,
};

/*
* class Container
*
* defines a rectanglular region of space in an index
* used to make procedurally generated maps
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Container
{
public:

	//span of the container
	int minX = 0;
	int minY = 0;
	int maxX = 0;
	int maxY = 0;

	//direction to split the container along
	Direction splitDirection = Direction::Null;
	
	//pointers to sub-containers of the container
	//used by BSP dungeon generation
	Container* leftChild = nullptr;
	Container* rightChild = nullptr;

	/*
	* Container()
	* default constructor
	*/
	Container() {};

	/*
	* ~Container()
	* destructor - deletes all of the sub-containers (leftChild / rightChild) recursively
	*/
	~Container();

	/*
	* split
	* 
	* creates two sub-containers by picking a random point
	* along the x or y axis (splitDirection) to split the room
	*
	* @param int recursionLevel - amount of times to recursively apply the split
	* @param float clamp - the clamp of the random pivot point
	* @returns void
	*/
	void split(int recursionLevel, float clamp);

	/*
	* centre
	*
	* gets the point at the centre of the container
	*
	* @returns index2D - the index of the centre of the container
	*/
	index2D centre();

	/*
	* erase
	*
	* removes the wall entity from the 2D array 
	* does nothing if the index is outside the range of the array
	*
	* @param std::vector<std::vector<WallEntity*>>& wall2D - reference to the 2D array of wall entities
	* @param int i - index of the 1st dimension
	* @param int j - index of the 2nd dimension
	* @returns void
	*/
	void erase(std::vector<std::vector<WallEntity*>>& wall2D, int i, int j);

	/*
	* eraseRegion
	*
	* removes a region of wall entities from the 2D array
	* does nothing if the index is outside the range of the array
	*
	* @param std::vector<std::vector<WallEntity*>>& wall2D - reference to the 2D array of wall entities
	* @param int minI - start index of the 1st dimension
	* @param int minJ - start index of the 2nd dimension
	* @param int maxI - end index of the 1st dimension
	* @param int maxJ - end index of the 2nd dimension
	* @returns void
	*/
	void eraseRegion(std::vector<std::vector<WallEntity*>>& wall2D, int minI, int minJ, int maxI, int maxJ);

};