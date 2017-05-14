#pragma once
#include <vector>

#include "partition.h"
#include "base_entity.h"
#include "wall_entity.h"
#include "player_entity.h"
#include "enemy_entity.h"
#include "projectile_entity.h"
#include "weapon_entity.h"
#include "car_entity.h"
#include "seat_entity.h"
#include "mount_entity.h"

#define FACTORY Factory::getInstance()

/*
* class Factory
*
* a singleton class that stores default layouts for
* objects that are repeatedly spawned and spawns them when needed
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class Factory
{
public:

	Application2D* appPtr; //pointer to the application, used to get textures

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the singleton
	* creates the object if the static pointer hasn't been assigned
	*
	* @returns static Factory* - a pointer to the only instance
	*/
	static Factory* getInstance();

	/*
	* createEnviromentWall
	*
	* creates a new wall instance with preset parameters
	* to be immoveable when updated by the physics engine
	*
	* @returns WallEntity* - a pointer to the newly created WallEntity
	*/
	WallEntity* createEnviromentWall();

	/*
	* fillWithEnviromentWall
	*
	* creates a large amount of new wall instances with preset parameters
	* that fill a region of space evenly
	*
	* @param Vector2 origin - the bottom-left corner of the fill region
	* @param Vector2 nodeSpan - how big the fill region is wallwise accross the x and y axes
	* @returns std::vector<std::vector<WallEntity*>> - a 2D array of WallEntity pointers
	*/
	std::vector<std::vector<WallEntity*>> fillWithEnviromentWall(Vector2 origin, Vector2 nodeSpan);

	/*
	* createPlayer
	*
	* creates a new player instance with preset parameters
	* to react to collisions linearly, but have no change in angular momentum
	* places the player on the root pathnode (middle of the map)
	*
	* @param Path* path - the pathfinding data, used to spawn the player at a suitable location
	* @returns PlayerEntity* - a pointer to the newly created PlayerEntity
	*/
	PlayerEntity* createPlayer(Path* path);

	/*
	* createEnemy
	*
	* creates a new enemy instance with preset parameters
	* to react to collisions linearly, but have no change in angular momentum
	* places the enemy on a random path node that neighbours the closest path node to the player
	*
	* @param Path* path - the pathfinding data, used to spawn the enemy at a suitable location
	* @param PlayerEntity* - the player entity that the enemy will chase
	* @returns EnemyEntity* - a pointer to the newly created EnemyEntity
	*/
	EnemyEntity* createEnemy(Path* path, PlayerEntity* player);

	/*
	* createMultipleEnemies
	*
	* creates multiple enemies with preset parameters at the same time
	*
	* @param Path* path - the pathfinding data, used to spawn the enemy at a suitable location
	* @param PlayerEntity* - the player entity that the enemy will chase
	* @param int amount - the amount of entities to place
	* @returns std::vector<EnemyEntity*> - an array of EnemyEntity pointers
	*/
	std::vector<EnemyEntity*> createMultipleEnemies(Path* path, PlayerEntity* player, int amount);

	/*
	* createProjectile
	*
	* creates a new projectile instance with preset parameters
	* to bounce off every perfectly elastically and rotate
	*
	* @param ProjectileType projectileType - the type of projectile to create
	* @returns ProjectileEntity* - a pointer to the newly created ProjectileEntity
	*/
	ProjectileEntity* createProjectile(ProjectileType projectileType);

	/*
	* createWeapon
	*
	* creates a weapon instance with preset parameters
	* to process collisions and be parented to players
	*
	* @param WeaponType weaponType - the type of weapon to create
	* @returns WeaponEntity* - a pointer to the newly created WeaponEntity
	*/
	WeaponEntity* createWeapon(WeaponType weaponType);

	/*
	* createCar
	*
	* creates a car instance with preset parameters
	* to process collisions and be parented to players
	*
	* @param Path* path - the pathfinding data, used to spawn the car at a suitable location
	* @returns CarEntity* - a pointer to the newly created CarEntity
	*/
	CarEntity* createCar(Path* path);

	/*
	* createCrate
	*
	* creates a base entity instance with preset parameters to appear and act like a crate
	* gets created at a random location in the map
	* 
	* @param Path* path - the pathfinding data, used to spawn the crate at a suitable location
	* @returns BaseEntity* - a pointer to the newly created crate
	*/
	BaseEntity* createCrate(Path* path);

	/*
	* createRock
	*
	* creates a base entity instance with preset parameters to appear and act like a rock
	* gets created at a random location in the map
	*
	* @param Path* path - the pathfinding data, used to spawn the crate at a suitable location
	* @returns BaseEntity* - a pointer to the newly created rock
	*/
	BaseEntity* createRock(Path* path);

	/*
	* createSeat
	*
	* creates a seat instance with preset parameters
	* to be parented to cars and have players parented to it
	*
	* @returns SeatEntity* - a pointer to the newly created seat
	*/
	SeatEntity* createSeat();

	/*
	* createMount
	*
	* creates a mount instance with preset parameters
	* to be parented to cars and have weapons parented to it
	*
	* @returns MountEntity* - a pointer to the newly created mount
	*/
	MountEntity* createMount();

	/*
	* registerRegularCar
	*
	* creates a car with four seats and places
	* it in the partition
	*
	* @param SpatialPartition* world - the world to put the car in
	* @param Path* path - the pathfinding data, used to spawn the car at a suitable location
	* @returns void
	*/
	void registerRegularCar(SpatialPartition* world, Path* path);

	/*
	* registerPickupCar
	*
	* creates a car with two seats and a mount
	* and places it in the partition
	*
	* @param SpatialPartition* world - the world to put the car in
	* @param Path* path - the pathfinding data, used to spawn the car at a suitable location
	* @returns void
	*/
	void registerPickupCar(SpatialPartition* world, Path* path);

protected:

	//as per the singleton structure

	/*
	* Factory()
	* default constructor
	*/
	Factory() {};

	/*
	* Factory()
	* default destructor
	*/
	~Factory() {};

};