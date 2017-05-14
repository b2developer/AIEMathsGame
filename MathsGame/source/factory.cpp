#include "factory.h"
#include "Application2D.h"

//get a pointer to the singleton
Factory * Factory::getInstance()
{
	//is defined at the start of the program
	static Factory* singleton = nullptr;

	//if the pointer contains no instance, assign one
	if (singleton == nullptr)
	{
		singleton = new Factory{};
	}

	return singleton;
}

//creates a single wall
WallEntity * Factory::createEnviromentWall()
{
	WallEntity* newWall = new WallEntity{appPtr};
	return newWall;
}

//creates a 2D array of walls at a specified origins
std::vector<std::vector<WallEntity*>> Factory::fillWithEnviromentWall(Vector2 origin, Vector2 nodeSpan)
{
	std::vector<std::vector<WallEntity*>> walls;

	//create a 2D array of wall entities
	for (int i = 0; i < nodeSpan.y; i++)
	{
		//add the row
		std::vector<WallEntity*> row;
		walls.push_back(row);

		for (int j = 0; j < nodeSpan.x; j++)
		{
			//create a new wall instance
			WallEntity* newWall = createEnviromentWall();

			//place the new wall correctly
			newWall->collider->transform.translation = origin + Vector2{ (float)newWall->wallTexture->getWidth() * j, 
																		 (float)newWall->wallTexture->getHeight() * i };
			walls[i].push_back(newWall);
		}
	}

	return walls;
}

//creates a single player
PlayerEntity * Factory::createPlayer(Path* path)
{
	PlayerEntity* newPlayer = new PlayerEntity{appPtr, path};
	return newPlayer;
}

//creates a single enemy
EnemyEntity * Factory::createEnemy(Path* path, PlayerEntity* player)
{
	EnemyEntity* newEnemy = new EnemyEntity{appPtr, path, player};
	return newEnemy;
}

//creates an array of enemies
std::vector<EnemyEntity*> Factory::createMultipleEnemies(Path * path, PlayerEntity * player, int amount)
{
	std::vector<EnemyEntity*> enemies;

	//iterate through the enemies array
	for (int i = 0; i < amount; i++)
	{
		enemies.push_back(createEnemy(path, player));
	}

	return enemies;
}

//creates a single projectile
ProjectileEntity * Factory::createProjectile(ProjectileType projectileType)
{
	ProjectileEntity* newProj = new ProjectileEntity{appPtr, projectileType};
	return newProj;
}

//creates a single weapon
WeaponEntity * Factory::createWeapon(WeaponType weaponType)
{
	WeaponEntity* newWeapon = new WeaponEntity{appPtr, weaponType};
	return newWeapon;
}

//create car
CarEntity * Factory::createCar(Path * path)
{
	CarEntity* newCar = new CarEntity{appPtr, path};
	return newCar;
}

//create crate base entity
BaseEntity * Factory::createCrate(Path * path)
{
	BaseEntity* newCrate = new BaseEntity{};

	//crates are base entities, hence they cannot be hardcoded into the constructor
	newCrate->baseTexture = appPtr->crateTexture; //assign texture

	Vector2 span = Vector2{ (float)newCrate->baseTexture->getWidth(), (float)newCrate->baseTexture->getHeight() };

	//create a hitbox that has the same dimensions as the texture
	AABB* hitbox = new AABB{ span * -0.5f, span * 0.5f };
	newCrate->collider = hitbox;

	newCrate->mass = 5.0f;
	newCrate->calculateMass(); //figures out the other mass-related variables based on regular mass

	newCrate->friction = 0.01f; //little friction
	newCrate->restitution = 0.5f; //half bounce

	size_t nodeSize = path->nodes.size();

	int randNum = rand() % nodeSize;

	newCrate->collider->transform.translation = path->nodes[randNum]->position;

	newCrate->collider->layer = 0b10100;

	return newCrate;
}

//create rock base entity
BaseEntity * Factory::createRock(Path * path)
{
	BaseEntity* newRock = new BaseEntity{};

	//rocks are base entities, hence they cannot be hardcoded into the constructor
	newRock->baseTexture = appPtr->rockTexture; //assign texture

	Vector2 span = Vector2{ (float)newRock->baseTexture->getWidth(), (float)newRock->baseTexture->getHeight() };

	//create a polygon that suits the texture
	Vector2 COM = Vector2{ 0,10 + 2.0f / 3.0f };

	newRock->centreOffset = COM;

	Polygon* poly = new Polygon{ std::vector<Vector2>{Vector2{0,32} + COM, Vector2{32,-32} + COM, Vector2{-32,-32} + COM} };
	newRock->collider = poly;

	newRock->mass = 5.0f;
	newRock->calculateMass(); //figures out the other mass-related variables based on regular mass

	newRock->friction = 0.01f; //little friction
	newRock->restitution = 0.5f; //half bounce

	size_t nodeSize = path->nodes.size();

	int randNum = rand() % nodeSize;

	newRock->collider->transform.translation = path->nodes[randNum]->position;
	newRock->collider->transform.scale = { 2,2 };
	newRock->collider->layer = 0b10100;

	return newRock;
}

//create seat entity
SeatEntity * Factory::createSeat()
{
	SeatEntity* newSeat = new SeatEntity{appPtr};	
	return newSeat;
}

//create mount entity
MountEntity * Factory::createMount()
{
	MountEntity* newMount = new MountEntity{appPtr};
	return newMount;
}
 
//creata a regular car and put it in the partition
void Factory::registerRegularCar(SpatialPartition * world, Path * path)
{
	CarEntity* newCar = FACTORY->createCar(path);

	//create 4 seats at different spots
	SeatEntity* seat1 = FACTORY->createSeat();
	SeatEntity* seat2 = FACTORY->createSeat();
	SeatEntity* seat3 = FACTORY->createSeat();
	SeatEntity* seat4 = FACTORY->createSeat();

	//parent the seats
	newCar->collider->transform.addChild(&seat1->collider->transform);
	newCar->collider->transform.addChild(&seat2->collider->transform);
	newCar->collider->transform.addChild(&seat3->collider->transform);
	newCar->collider->transform.addChild(&seat4->collider->transform);

	seat1->car = newCar;
	seat2->car = newCar;
	seat3->car = newCar;
	seat4->car = newCar;

	//register the car and seats
	world->registerCollider(newCar, true);
	world->registerCollider(seat1, true);
	world->registerCollider(seat2, true);
	world->registerCollider(seat3, true);
	world->registerCollider(seat4, true);

	//set the local translation of the seats
	seat1->collider->transform.translation = Vector2{ -50,50 };
	seat2->collider->transform.translation = Vector2{ 50,50 };
	seat3->collider->transform.translation = Vector2{ -50,-50 };
	seat4->collider->transform.translation = Vector2{ 50,-50 };

	//add pointers to seats
	newCar->seats.push_back(seat1);
	newCar->seats.push_back(seat2);
	newCar->seats.push_back(seat3);
	newCar->seats.push_back(seat4);
}

//create a pickup car and put it in the partition
void Factory::registerPickupCar(SpatialPartition * world, Path * path)
{
	CarEntity* newCar = FACTORY->createCar(path);

	newCar->carTexture = appPtr->redCarTexture;

	//create 2 seats and 2 mounts at different spots
	SeatEntity* seat1 = FACTORY->createSeat();
	SeatEntity* seat2 = FACTORY->createSeat();
	MountEntity* mount1 = FACTORY->createMount();
	MountEntity* mount2 = FACTORY->createMount();

	//parent the seats
	newCar->collider->transform.addChild(&seat1->collider->transform);
	newCar->collider->transform.addChild(&seat2->collider->transform);
	newCar->collider->transform.addChild(&mount1->collider->transform);
	newCar->collider->transform.addChild(&mount2->collider->transform);

	seat1->car = newCar;
	seat2->car = newCar;
	mount1->car = newCar;
	mount2->car = newCar;

	//register the car, seats and mounts
	world->registerCollider(newCar, true);
	world->registerCollider(seat1, true);
	world->registerCollider(seat2, true);
	world->registerCollider(mount1, true);
	world->registerCollider(mount2, true);

	//set the local translation of the seats and mounts
	seat1->collider->transform.translation = Vector2{ -50,50 };
	seat2->collider->transform.translation = Vector2{ 50,50 };
	mount1->collider->transform.translation = Vector2{ -50,-50 };
	mount2->collider->transform.translation = Vector2{ 50,-50 };

	//add pointers to seats
	newCar->seats.push_back(seat1);
	newCar->seats.push_back(seat2);

	//add pointers to mounts
	newCar->mounts.push_back(mount1);
	newCar->mounts.push_back(mount2);
}

