#pragma once
#include "base_entity.h"

//macro that defines the instance with a name
#define COLL_SOLVER CollisionSolver::getInstance()

/*
* struct SimpleCollision
*
* contains useful information about a collision
* - which shapes were involved
* - the minimum vector required to seperate them
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct SimpleCollision
{
	bool intersection = false; //did an intersection take place

	Collider* A; //the first collider in the collision test
	Collider* B; //the second collider in the collision test

	Vector2 MTV; //minimum translation vector
};

/*
* struct AdvancedCollision
*
* contains useful information about a collision
* - which bodies were involved
* - the minimum vector required to seperate them, based on their velocities
* - how to resolve the collision, and when the collision occured
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct AdvancedCollision
{
	bool intersection = false; //did an intersection take place

	BaseEntity* A; //the first entity in the collision test
	BaseEntity* B; //the second entity in the collision test

	int A_index = 0;
	int B_index = 0;

	Vector2 MTV; //minimum translation vector
	Vector2 normal; //direction of collision
	Vector2 A_contact; //contact point relative to A
	Vector2 B_contact; //contact point relative to B

};

/*
* class CollisionSolver
* 
* a singleton class that calculates collisions between
* various shapes and returns detailed information about collisions
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class CollisionSolver
{
public:

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the singleton
	* creates the object if the static pointer hasn't been assigned
	*
	* @returns static CollisionSolver* - a pointer to the only instance
	*/
	static CollisionSolver* getInstance();

	/*
	* doSimpleIntersectionTest
	*
	* uses the Seperating Axis Theorem (SAT) to deduce if two
	* shapes are intersecting
	*
	* https://tinyurl.com/zgx3n38 (tiny url link to explaination)
	*
	* SAT works by casting shadows in the direction of every axis
	* on both the shapes and attempts to find a gap
	* 
	* if one gap is found, SAT exits because they are not colliding
	* if a gap is not found, the shapes are intersecting
	*
	* @param Collider* A - the first shape to test
	* @param Collider* B - the second shape to test
	* @returns bool - the result of the intersection test
	*/
	bool doSimpleIntersectionTest(Collider* A, Collider* B);

	/*
	* doAdvancedIntersectionTest
	*
	* uses the Seperating Axis Theorem (SAT) to deduce if two
	* shapes are intersecting, and then resolves the collision
	*
	* @param Collider* A - the first shape to test
	* @param Collider* B - the second shape to test
	* @returns Collision - detailed information about the intersection test
	*/
	SimpleCollision doAdvancedIntersectionTest(Collider* A, Collider* B);

	/*
	* doBaseEntityIntersectionTest
	*
	* uses the Seperating Axis Theorem (SAT) to deduce if two
	* shapes are intersecting, and information on how to resolve the collision
	*
	* @param BaseEntity* A - the first baseEntity to test
	* @param BaseEntity* B - the second baseEntity to test
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns Collision - detailed information about the intersection test
	*/
	AdvancedCollision doBaseEntityIntersectionTest(BaseEntity* A, BaseEntity* B, float deltaTime);

	/*
	* calculateContacts
	*
	* takes a partially completed advanced collision and uses support functions
	* to add contact points to the collision information
	*
	* @param AdvancedCollision partial - the advanced collision that took place and was resolved
	* @returns AdvancedCollision - 'partial' with contact points
	*/
	AdvancedCollision calculateContacts(AdvancedCollision partial);

protected:

	//as per the singleton structure

	/*
	* CollisionSolver()
	* default constructor
	*/
	CollisionSolver() {};

	/*
	* CollisionSolver()
	* default destructor
	*/
	~CollisionSolver() {};
};


