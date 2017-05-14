#pragma once
#include "collision.h"

//macro that defines the instance with a name
#define PHYS_SOLVER PhysicsSolver::getInstance()

/*
* class PhysicsSolver
*
* a singleton class that calculates the resulting changes in velocity
* and angular velocity that result from gravity, collisions or other forces
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class PhysicsSolver
{
public:

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the singleton
	* creates the object if the static pointer hasn't been assigned
	*
	* @returns static PhysicsSolver* - a pointer to the only instance
	*/
	static PhysicsSolver* getInstance();

	/*
	* applyImpulse
	*
	* uses information about a collision to update the two object's velocities
	* the objects are accessed as pointers from the AdvancedCollision argument
	*
	* @param AdvancedCollision coll - the collision data to calculate the impulses from
	* @returns void
	*/
	void applyImpulse(AdvancedCollision coll);

protected:

	//as per the singleton structure

	/*
	* PhysicsSolver()
	* default constructor
	*/
	PhysicsSolver() {};

	/*
	* PhysicsSolver()
	* default destructor
	*/
	~PhysicsSolver() {};
};

