#pragma once
#include <vector>
#include "wall_entity.h"
#include "container.h"
#include "path.h"

#define BSPGEN BSPGenerator::getInstance()

/*
* class BSPGenerator
*
* a singleton class that generates maps from container classes
* and inprints the map into a 2D entity array
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class BSPGenerator
{
public:

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the singleton
	* creates the object if the static pointer hasn't been assigned
	*
	* @returns static BSPGenerator* - a pointer to the only instance
	*/
	static BSPGenerator* getInstance();

	/*
	* eraseRecursive
	*
	* executes Container's eraseRegion using the last child of the container along every branch of the tree
	*
	* @param std::vector<std::vector<WallEntity*>>& map - reference to the 2D array of wall entities to dig out rooms and corridors from
	* @param Container container - the container to get children from
	* @returns void
	*/
	void eraseRecursive(std::vector<std::vector<WallEntity*>>& map, Container* container);

	/*
	* connectBrothersRecursive
	*
	* executes Container's erase along a horizontal/vertical line formed by two brother sub-containers
	* brothers are sub-containers with the same immediate parent
	*
	*		container
 	*        /     \
	*       /       \         sub1 and sub2 are brothers
	*      /         \
	*   sub1         sub2
	*
	* @param std::vector<std::vector<WallEntity*>>& map - reference to the 2D array of wall entities to dig out rooms and corridors from
	* @param Container container - the container to get children from
	* @returns void
	*/
	void connectBrothersRecursive(std::vector<std::vector<WallEntity*>>& map, Container* container);

	/*
	* generateMap
	*
	* map generation process:
	* -----------------------------------------------------------------------------
	* 1.
	* split a container recusively along randomly placed split lines,
	* flipping the direction that the split occurs along at every recursion level. 
	*
	* 2.
	* dig out the map using the regions of the sub-containers that have no children
	*
	* 3.
	* connect the map by filling in the line connecting each brother in the binary tree,
	* two sub-containers that have the same immediate parent are brothers
	* -----------------------------------------------------------------------------
	*
	* @param std::vector<std::vector<WallEntity*>>& map - reference to the 2D array of wall entities to dig out rooms and corridors from
	* @param Path& pathMap - reference to the Path that will be given nodes and connections that represent the map
	* @param int recursionLevel - amount of times to recursively split the base container
	* @param float clamp - scalar of how far from each end the random pivot point will be (1 = no change, 0.5 = between 0.25 and 0.75)
	* @returns void
	*/
	void generateMap(std::vector<std::vector<WallEntity*>>& map, Path& pathMap, int recursionLevel, float clamp);


protected:

	//as per the singleton structure

	/*
	* BSPGenerator()
	* default constructor
	*/
	BSPGenerator() {};

	/*
	* BSPGenerator()
	* default destructor
	*/
	~BSPGenerator() {};

};