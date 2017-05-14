#include "wall_entity.h"
#include "Application2D.h"

//default value constructor
WallEntity::WallEntity(Application2D* appPtr)
{
	type = EntityType::WALL;

	wallTexture = appPtr->wallTexture; //assign texture

	//get the width and height of the texture
	Vector2 span = Vector2{ (float)wallTexture->getWidth(), (float)wallTexture->getHeight() };

	//create a hitbox that has the same dimensions as the texture
	AABB* hitbox = new AABB{ span * -0.5f, span * 0.5f };
	collider = hitbox;

	mass = 0.0f;
	calculateMass(); //figures out the other mass-related variables based on regular mass

	friction = 0.0f; //no friction
	restitution = 1.0f; //perfect bounce

	collider->layer = 0b11100;
}

//walls do not do anything
void WallEntity::update(float deltaTime, Application2D* appPtr)
{
}

//renders the wall
void WallEntity::render(Application2D* appPtr)
{
	//the rotation occurs from the top-left corner
	//use another matrix to force entities to rotate from the centre
	Matrix3 correction = Matrix3{};
	correction.identity();
	correction[2][0] = wallTexture->getWidth() / -2.0f;
	correction[2][1] = wallTexture->getHeight() / -2.0f;

	appPtr->m_2dRenderer->drawSpriteTransformed3x3(wallTexture, collider->transform.globalTransform * correction, 0.0f, 0.0f, 0, 0.0f, 0.0f);
}
