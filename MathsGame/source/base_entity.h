#pragma once
#include "collider.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "AABB.h"
#include "polygon.h"

#include "Texture.h"

//enum for defining the types of entities
enum class EntityType
{
	BASE,
	WALL,
	PLAYER,
	ENEMY,
	PROJECTILE,
	WEAPON,
	CAR,
	SEAT,
	MOUNT,
};

/*
* class BaseEntity
*
* updates using velocity, rotation and a collider
* to interact with other bodies
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class BaseEntity
{
public:

	Collider* collider; //the shape of the baseEntity
	Vector2 centreOffset; //texture offset

	EntityType type = EntityType::BASE; //a cached typeid

	bool colliding = true; //flag that indicates if the shape will affect other shapes
	bool awake = true; //flag that indicates if the shape recieves update calls
	bool reactive = true; //flag that indicates that the shape will react to collisions physically

	float mass = 1; //a mass of 0 means an infinite mass
	float invMass = 1; //inverse mass is useful for physics calaculations

	float inertia = 1; //rotational mass, how much energy is stored is equal to angular velocity * inertia
	float invInertia = 1; //as with inverse mass, inverse inertia is also useful for physics calculations

	float restitution = 1.0f; //ratio of how much energy is lost in a collision
	float friction = 0.0f; //ratio of how much force along the face a collided with is lost during a collision

	Vector2 velocity = Vector2{}; //the change in position every second
	float angularVelocity = 0.0f; //the change in rotation (radians) every second

	aie::Texture * baseTexture = nullptr; //texture used to draw the entity

	/*
	* BaseEntity()
	* constructor - assigns the inverse mass
	*/
	BaseEntity();

	/*
	* BaseEntity()
	* constructor - assigns collider from a pointer
	* 
	* @param Collider* _collider - the pointer to assign internally
	*/
	BaseEntity(Collider* _collider);

	/*
	* ~BaseEntity()
	* destructor - deletes the collider
	*/
	~BaseEntity() { delete collider; };
	
	/*
	* calculateMass
	* 
	* calculates mass related variables such as inverse mass and inertia
	* based on the regular mass of the baseEntity
	*
	* @returns void
	*/
	void calculateMass();

	/*
	* collisionCallBack
	* virtual function
	*
	* this function gets called when the collision engine detects a
	* collision that this entity is involved in
	*
	* @param BaseEntity* other - the other entity that was involved in the collision
	* @returns void
	*/
	virtual void collisionCallBack(BaseEntity* other);

	/*
	* update
	* virtual function
	*
	* runs the game logic for the entity, given the application
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @param Application2D* appPtr - application to get info from on how to update
	* @returns void
	*/
	virtual void update(float deltaTime, Application2D* appPtr);

	/*
	* render
	* virtual function
	*
	* renders the object to the screen 
	*
	* @param Application2D* appPtr - the application that contains the renderer
	* @returns void
	*/
	virtual void render(Application2D* appPtr);
};