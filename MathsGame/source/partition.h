#pragma once
#include <vector>
#include "base_entity.h"
#include "collision.h"

/*
* struct SpatialPartitionEntityPair
*
* groups a partition position and an entity inside the partition
* together, greatly improves the speed of the partition
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct SpatialPartitionBodyPair
{
	int i;
	int j;
	BaseEntity* entity;
};

/*
* struct index2D
*
* index pair for a 2D array, i indexes the first dimension, j indexes the second dimension
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct index2D
{
	int i;
	int j;
};

/*
* class SpatialPartition
*
* monitors a region of space by checking the intersection of a 2D
* grid which transverses the region of space
*
* region of space (with objects inside it)
* ---------------------------
* |							|
* |		a		b	e		|
* |							|
* |			c				|
* |					d		|
* ---------------------------
*
* partitioning the space
* --------------------------- 
* |			  |				|
* |		a	  |	b	e		|
* |-----------|-------------|
* |			c |				|
* |			  |		d		|
* ---------------------------
* a partition of this region will contain 4 vectors; (a), (b,e), (c) and (d)
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class SpatialPartition
{
public:

	BaseEntity* root; //special object which is the parent of all other objects in the partition

	Vector2 origin; //the bottom-left corner of the partition
	float nodeSize = 0; //size of an individual node, all colliders must not suceed 3 times this accross any axis
	int iLength = 0; //length of the 2D array (1st dimension)
	int jLength = 0; //length of the 2D array (2nd dimension)

	std::vector<SpatialPartitionBodyPair> entities; //array of entities to go through
	std::vector<std::vector<std::vector<BaseEntity*>>> nodes; //partition data, a 2D array of arrays of entites

	/*
	* SpatialPartition()
	* default constructor
	*/
	SpatialPartition();

	/*
	* ~SpatialPartition()
	* destructor - deletes all colliders contained by it
	*/
	~SpatialPartition();

	/*
	* initialisePartition
	*
	* adds enough the required amount of arrays to the partition
	*
	* @returns void
	*/
	void initialisePartition();

	/*
	* registerCollider
	* 
	* attempts to add an entity to the partition
	* the collider must take up less space than a square with a side length equal to 3 times the nodeSize
	*
	* @param BaseEntity* entity - the collider to register
	* @param bool full - whether or not to add the collider to the main array of partitioned objects (entities)
	* @returns bool - flag indicating if the registration succeeded
	*/
	bool registerCollider(BaseEntity* entity, bool full);

	/*
	* removeCollider
	*
	* removes all instances of the entity from the partition
	* a pointer to the pointer must be used to prevent copying of the actual pointer.
	* this is necessary since the pointer is assigned to nullptr after a delete
	*
	* @param BaseEntity** entitydPtr - pointer to a pointer to the collider to remove
	* @param bool full - whether or not to get rid of the collider from the partition entirely
	* 
	* @returns void
	*/
	void removeCollider(BaseEntity** entitydPtr, bool full, int id);

	/*
	* testCollider
	*
	* test a collider against the partition that isn't in the partition
	*
	* @param Collider* coll - the collider to test
	*
	* @returns std::vector<BaseEntity*> - list of all colliding entities
	*/
	std::vector<BaseEntity*> testCollider(Collider* collider);

	/*
	* getNeighbours
	*
	* gets the neighbouring entities that the collider could be potentially colliding with
	*
	* @param Collider* collider - the collider to get neighbours from
	* @returns std::vector<Collider*> - list of potential collision partners
	*/
	std::vector<BaseEntity*> getNeighbours(Collider* collider);

	/*
	* getNeighbours
	*
	* gets the neighbouring entities that the entity could be  potentially colliding with
	*
	* @param BaseEntity* entity - the collider to get neighbours from
	* @returns std::vector<Collider*> - list of potential collision partners
	*/
	std::vector<BaseEntity*> getNeighbours(BaseEntity* entity);

	/*
	* updateAll
	*
	* updates all of the entities inside the partition
	*
	* @param Application2D* appPtr - pointer to the application2D to render the entity to
	* @param float deltaTime - amount of time passed since the last frame
	* @returns void
	*/
	void updateAll(float deltaTime, Application2D* appPtr);

	/*
	* renderAll
	*
	* renders all entities inside the partition
	*
	* @param Application2D* appPtr - pointer to the application2D to render the entity to
	* @returns void
	*/
	void renderAll(Application2D* appPtr);

};