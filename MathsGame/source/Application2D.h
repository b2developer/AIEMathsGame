#pragma once
#include "Application.h"

#include "Renderer2D.h"

#include "file_manager.h"
#include "maths_library.h"

#include "partition.h"
#include "path.h"

/*
* class Application2D
* child class of aie::Application
*
* responsible for updating the game and managing the viewport
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Application2D : public aie::Application
{
public:

	/*
	* Application2D()
	* default constructor
	*/
	Application2D();

	/*
	* ~Application2D()
	* virtual function
	* default destructor
	*/
	virtual ~Application2D();

	/*
	* loadTexture
	* 
	* attempts to load a texture, will keep attempting to
	* load the texture until it succeeds
	*
	* @param aie::Texture*&  texPtr - reference the texture pointer to put the loaded data in
	* @param std::string filePath - path to the texture
	* @returns void
	*/
	void loadTexture(aie::Texture*& texPtr, std::string filePath);

	/*
	* startup
	* virtual function
	*
	* runs once when the Application2D is started, initialises all of the variables
	* 
	* runs when the application is started
	* @returns bool - indicates if the startup was sucessful
	*/
	virtual bool startup();

	/*
	* shutdown
	* virtual function
	*
	* runs once when the Application2D is ended, deallocates all of the variables
	* that require deallocating
	*
	* runs when the application is stopped
	* @returns void
	*/
	virtual void shutdown();

	/*
	* update
	* virtual function
	*
	* runs one frame of game logic
	*
	* @param float - the amount of time passed since the last update call	
	* @returns void
	*/
	virtual void update(float deltaTime);

	/*
	* draw
	* virtual function
	*
	* draws the current game state to the screen
	*
	* @returns void
	*/
	virtual void draw();

	//the renderer object
	aie::Renderer2D* m_2dRenderer;

	//the file manager, contains all file paths (textures, .txts, sounds, fonts)
	FileManager* m_fileManager;

	//textures
	aie::Texture* wallTexture;
	aie::Texture* playerTexture;
	aie::Texture* enemyTexture;
	aie::Texture* projectileTexture;
	aie::Texture* crateTexture;
	aie::Texture* rockTexture;

	//weapon textures
	aie::Texture* flamethrowerTexture;
	aie::Texture* shotgunTexture;
	aie::Texture* uziTexture;

	//car textures
	aie::Texture* blueCarTexture;
	aie::Texture* redCarTexture;
	aie::Texture* seatTexture;
	aie::Texture* mountTexture;

	//has all of the gameobjects connected to it, used to recursively update all of the entities
	BaseEntity* root;

	//index in the entities array that refers to the player
	int playerIndex = 0;

	//the world stored as a static grid 
	SpatialPartition world;
	Path path;

	//position of the camera
	Vector2 m_camera;

};