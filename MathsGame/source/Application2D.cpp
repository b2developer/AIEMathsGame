#include "Application2D.h"

#include "Texture.h"
#include "Font.h"
#include "Audio.h"
#include "Input.h"

#include "maths_library.h"
#include "factory.h"
#include "bsp_generator.h"
#include "path.h"

#include "collision.h"
#include "transform.h"

#include "base_entity.h"
#include "wall_entity.h"
#include "player_entity.h"
#include "weapon_entity.h"

//constructor
Application2D::Application2D()
{
	
}

//destructor
Application2D::~Application2D()
{

}

//load a texture
void Application2D::loadTexture(aie::Texture*& texPtr, std::string filePath)
{
	texPtr = new aie::Texture(filePath.c_str());

	const unsigned char * pixels = texPtr->getPixels();
	char pixel = pixels[0];

	int i = 0;
	while (pixels[i] != '\0' && pixels[i] == pixel)
	{
		i++;
	}

	if (i > 100)
	{
		std::vector<Vector2> garbage;
		garbage.push_back(Vector2{ 0,0 });
	}
}

//run initialisation for the application
bool Application2D::startup()
{

	//vsync
	setVSync(false);

	//load textures
	loadTexture(wallTexture, m_fileManager->resourcePath + "bricks.png");
	loadTexture(playerTexture, m_fileManager->resourcePath + "player.png");
	loadTexture(enemyTexture, m_fileManager->resourcePath + "enemy.png");
	loadTexture(projectileTexture, m_fileManager->resourcePath + "projectile.png");
	loadTexture(rockTexture, m_fileManager->resourcePath + "rock.png");
	loadTexture(crateTexture, m_fileManager->resourcePath + "crate.png");

	//load weapon textures
	loadTexture(flamethrowerTexture, m_fileManager->resourcePath + "flamethrower.png");
	loadTexture(shotgunTexture, m_fileManager->resourcePath + "shotgun.png");
	loadTexture(uziTexture, m_fileManager->resourcePath + "uzi.png");

	//load car textures
	loadTexture(blueCarTexture, m_fileManager->resourcePath + "car.png");
	loadTexture(redCarTexture, m_fileManager->resourcePath + "red_car.png");
	loadTexture(seatTexture, m_fileManager->resourcePath + "seat.png");
	loadTexture(mountTexture, m_fileManager->resourcePath + "mount.png");

	FACTORY->appPtr = this;

	//root entity creation
	//-----------------------------------
	root = new BaseEntity{};

	root->collider = new Point{ Vector2{0,0} };

	root->awake = false;
	root->colliding = false;
	root->reactive = false;
	root->collider->layer = 0b0000;

	root->collider->transform = Transform{ Vector2{0,0}, 0.0f, Vector2{1,1} };
	root->collider->transform.updateGlobalTransform();

	world.root = root;
	//-----------------------------------

	world.nodeSize = 96.0f;
	world.iLength = 30;
	world.jLength = 30;

	world.initialisePartition();

	std::vector<std::vector<WallEntity*>> walls = FACTORY->fillWithEnviromentWall(Vector2{ 0,0 }, Vector2{ 30, 30 });

	BSPGEN->generateMap(walls, path, 2, 0.45f);

	//resize the generated pathfinding map to fit the world
	path.scale(96.0f);

	size_t wallsSize = walls.size();

	//iterate though the rows
	for (size_t i = 0; i < wallsSize; i++)
	{
		size_t rowSize = walls[i].size();

		//iterate through the row
		for (size_t j = 0; j < rowSize; j++)
		{
			if (walls[i][j] != nullptr)
			{
				world.registerCollider(walls[i][j], true);
			}
		}
	}

	PlayerEntity* player = FACTORY->createPlayer(&path);

	player->closestNode = player->getClosestNode(&world, &path);

	std::vector<EnemyEntity*> enemies = FACTORY->createMultipleEnemies(&path, player, 0);

	size_t enemySize = enemies.size();

	for (size_t i = 0; i < enemySize; i++)
	{
		world.registerCollider(enemies[i], true);
	}

	WeaponEntity* baseWeapon = FACTORY->createWeapon(WeaponType::FLAMETHROWER);
	WeaponEntity* baseWeapon2 = FACTORY->createWeapon(WeaponType::SHOTGUN);
	WeaponEntity* baseWeapon3 = FACTORY->createWeapon(WeaponType::UZI);
	WeaponEntity* baseWeapon4 = FACTORY->createWeapon(WeaponType::FLAMETHROWER);
	WeaponEntity* baseWeapon5 = FACTORY->createWeapon(WeaponType::SHOTGUN);
	WeaponEntity* baseWeapon6 = FACTORY->createWeapon(WeaponType::UZI);

	baseWeapon->collider->transform.translation = Vector2{ 200,200 };
	baseWeapon2->collider->transform.translation = Vector2{ 275,200 };
	baseWeapon3->collider->transform.translation = Vector2{ 350,200 };
	baseWeapon4->collider->transform.translation = Vector2{ 200,100 };
	baseWeapon5->collider->transform.translation = Vector2{ 275,100 };
	baseWeapon6->collider->transform.translation = Vector2{ 350,100 };

	FACTORY->registerRegularCar(&world, &path);
	FACTORY->registerPickupCar(&world, &path);

	world.registerCollider(baseWeapon, true);
	world.registerCollider(baseWeapon2, true);
	world.registerCollider(baseWeapon3, true);

	world.registerCollider(baseWeapon4, true);
	world.registerCollider(baseWeapon5, true);
	world.registerCollider(baseWeapon6, true);

	BaseEntity* crate = FACTORY->createCrate(&path);
	BaseEntity* crate2 = FACTORY->createCrate(&path);
	BaseEntity* crate3 = FACTORY->createCrate(&path);
	BaseEntity* crate4 = FACTORY->createCrate(&path);

	BaseEntity* rock = FACTORY->createRock(&path);
	BaseEntity* rock2 = FACTORY->createRock(&path);
	BaseEntity* rock3 = FACTORY->createRock(&path);
	BaseEntity* rock4 = FACTORY->createRock(&path);

	world.registerCollider(crate, true);
	world.registerCollider(crate2, true);
	world.registerCollider(crate3, true);
	world.registerCollider(crate4, true);

	world.registerCollider(rock, true);
	world.registerCollider(rock2, true);
	world.registerCollider(rock3, true);
	world.registerCollider(rock4, true);

	world.registerCollider(player, true);

	playerIndex = (int)world.entities.size() - 1;

	m_2dRenderer = new aie::Renderer2D();

	//m_texture = new aie::Texture();
	//m_font = new aie::Font();
 	//m_autio = new aie::Audio();

	m_camera = Vector2{ 0,0 };

	return true;
}

//stop the application
void Application2D::shutdown()
{
	delete wallTexture;
	delete playerTexture;
	delete enemyTexture;
	delete projectileTexture;
	delete crateTexture;
	delete rockTexture;

	//weapon textures
	delete flamethrowerTexture;
	delete shotgunTexture;
	delete uziTexture;

	//car textures
	delete blueCarTexture;
	delete redCarTexture;
	delete seatTexture;
	delete mountTexture;

	delete m_2dRenderer;
}

//update, called once per frame
void Application2D::update(float deltaTime)
{
	//get the input singleton
	aie::Input* input = aie::Input::getInstance();

	world.updateAll(deltaTime, this);

	//quit if the player presses escape
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

//draw the application, called once per frame
void Application2D::draw()
{
	//clear the screen back to the background colour
	clearScreen();

	//get the global matrix of the player
	Matrix3 transMatrix = world.entities[playerIndex].entity->collider->transform.globalTransform;

	//set the camera's position to the player
	m_camera = Vector2{ transMatrix[2][0], transMatrix[2][1] };
	m_camera += Vector2{ (float)getWindowWidth(), (float)getWindowHeight() } * -0.5f;

	//set the renderer's camera position to match the camera
	m_2dRenderer->setCameraPos(m_camera.x, m_camera.y);

	m_2dRenderer->begin();

	//set the renderer colour to render all colours
	m_2dRenderer->setRenderColour(1, 1, 1);	

	//render the world
	world.renderAll(this);

	m_2dRenderer->end();
}