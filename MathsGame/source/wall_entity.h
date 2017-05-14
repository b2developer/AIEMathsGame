#pragma once
#include "base_entity.h"
#include "Texture.h"

//forward declaration
class Application2D;

/*
* class WallEntity
* child class of BaseEntity
*
* a solid obstacle. never moves, gets placed once
* when the world gets generated, prevents other entities from moving through
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/

class WallEntity : public BaseEntity
{
public:

	aie::Texture * wallTexture; //texture used to draw the wall

	/*
	* WallEntity()
	* constructor, sets the type for the entity
	*/
	WallEntity() { type = EntityType::WALL; };

	/*
	* WallEntity()
	* constructor, sets the type for the entity and initialises it's default values
	*
	* @param Application2D* appPtr - application pointer, used to grab textures
	*/
	WallEntity(Application2D* appPtr);

	/*
	* ~WallEntity()
	* default destructor
	*/
	~WallEntity() {};

	/*
	* update
	* overrides BaseEntity's update()
	*
	* runs the game logic for the entity
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @param Application2D* appPtr - application to get info from on how to update
	* @returns void
	*/
	void update(float deltaTime, Application2D* appPtr) override;

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