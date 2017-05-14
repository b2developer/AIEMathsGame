#pragma once
#include "base_entity.h"
#include "player_entity.h"
#include "Texture.h"

//forward declaration
class Application2D;

/*
* class EnemyEntity
* child class of BaseEntity
*
* an entity that chases a target (the player) around the map
* using a pathfinding system
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class EnemyEntity : public BaseEntity
{
public:

	PlayerEntity* target; //player entity that the enemy is trying to get to
	
	float moveAcceleration = 1000.0f; //acceleration per second
	float moveFriction = 0.95f; //multiplication of movement speed every frame (frame dependent at 60FPS)

	float nodeEpsilon = 50.0f; //how close the enemy has to be to a pathfinding node before it moves towards the next one
	Node* closestNode; //closest pathfinding node (position) to the entity can be moved directly
	std::vector<Node*> pathList; //array of vectors to follow to get to the player

	aie::Texture * enemyTexture; //texture used to draw the enemy

	/*
	* EnemyEntity()
	* constructor, sets the type for the entity
	*/
	EnemyEntity() { type = EntityType::ENEMY; };

	/*
	* EnemyEntity()
	* constructor, sets the type for the entity and initialises default values
	*
	* @param Application2D* appPtr - application pointer, used to grab textures
	* @param Path* path - pointer to the map data, used to place the entity
	* @param PlayeeEntity* player - the player to target
	*/
	EnemyEntity(Application2D* appPtr, Path* path, PlayerEntity* player);

	/*
	* ~EnemyEntity()
	* default destructor
	*/
	~EnemyEntity() {};

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