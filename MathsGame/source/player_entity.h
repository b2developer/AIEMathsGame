#pragma once
#include "base_entity.h"
#include "weapon_entity.h"
#include "path.h"

#include "seat_entity.h"
#include "mount_entity.h"

#include "Texture.h"

//forward declaration
class Application2D;
class CarEntity;

/*
* class PlayerEntity
* child class of BaseEntity
*
* an entity that is controlled by human input, gives the player
* their presence in the game
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class PlayerEntity : public BaseEntity
{
public:

	float moveAcceleration = 2000.0f; //acceleration per second
	float moveFriction = 0.95f; //multiplication of movement speed every frame (frame dependent at 60FPS)

	Vector2 primaryWeaponOffset = Vector2{}; //offset of main weapon
	Vector2 secondaryWeaponOffset = Vector2{}; //offset of second weapon

	WeaponEntity* primaryWeapon = nullptr; //primary weapon that is being used
	WeaponEntity* secondaryWeapon = nullptr; //secondary weapon that is being used

	SeatEntity* seat = nullptr; //seat that is being used

	//collision information for interaction with other entities
	//-----------------------------------------------------------
	WeaponEntity* collidedWeapon = nullptr; //weapon that was highlighted with the mouse
	SeatEntity* collidedSeat = nullptr; //seat that was highlighted with the mouse
	MountEntity* collidedMount = nullptr; //mount that was highlighted with the mouse
	//-----------------------------------------------------------
	
	Node* closestNode; //closest pathfinding node (position) to the entity can be moved directly

	aie::Texture * playerTexture; //texture used to draw the player

	/*
	* PlayerEntity()
	* constructor, sets the type for the entity
	*/
	PlayerEntity() { type = EntityType::PLAYER; };

	/*
	* PlayerEntity()
	* constructor, sets the type for the entity and initialises default values
	*
	* @param Application2D* appPtr - application pointer, used to grab textures
	* @param Path* path - pointer to the map data, used to place the entity
	*/
	PlayerEntity(Application2D* appPtr, Path* path);

	/*
	* ~PlayerEntity()
	* default destructor
	*/
	~PlayerEntity() {};

	/*
	* collisionCallBack
	* overrides BaseEntity's collisionCallBack(BaseEntity* other)
	*
	* this function gets called when the collision engine detects a
	* collision that this entity is involved in
	*
	* @param BaseEntity* other - the other entity that was involved in the collision
	* @returns void
	*/
	void collisionCallBack(BaseEntity* other) override;

	/*
	* update
	* overrides BaseEntity's update(float deltaTime, Application2D* appPtr)
	*
	* runs the game logic for the entity, given the application
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @param Application2D* appPtr - application to get info from on how to update
	* @returns void
	*/
	void update(float deltaTime,  Application2D* appPtr) override;

	/*
	* getClosestNode
	*
	* gets the closest node from pathfinding data
  	* that the entity can move directly towards
	*
	* @param SpatialPartition* world - pointer to the game world
	* @param Path* path - the pathfinding data, interconnected nodes
	* @returns Node* - pointer to the closest node
	*/
	Node* getClosestNode(SpatialPartition* world, Path* path);

	/*
	* render
	* overrides BaseEntity's render()
	*
	* renders the object to the screen
	*
	* @param Application2D* appPtr - the application that contains the renderer
	* @returns void
	*/
	void render(Application2D* appPtr) override;
};