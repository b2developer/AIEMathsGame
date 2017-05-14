#include "base_entity.h"
#include "Application2D.h"

//constructor
BaseEntity::BaseEntity()
{

}

//constructor from pointer to shape
BaseEntity::BaseEntity(Collider * _collider)
{
	collider = _collider;
}

//calculate the mass, inverse mass, inertia and inverse inertia
void BaseEntity::calculateMass()
{
	//a mass of 0 = infinite mass in the physics engine
	if (mass == 0)
	{
		//only inverse mass is used by the physics engine
		//1 / infinity = 0
		invMass = 0;
	}
	else
	{
		//get the actual inverse otherwise
		invMass = 1 / mass;
	}

	//calculate the amount of inertia (rotational mass) that the collider has
	inertia = collider->momentOfInertia(mass);

	//an inertia of 0 = infinite inertia
	if (inertia == 0)
	{
		//only inverse inertia is used by the physics engine
		//1 / infinity = 0
		invInertia = 0;
	}
	else
	{
		//get the actual inverse otherwise
		invInertia = 1 / inertia;
	}

}

//base entities do not react to callbacks
void BaseEntity::collisionCallBack(BaseEntity * other)
{
}

//base entities have no physical capabilities
void BaseEntity::update(float deltaTime, Application2D* appPtr)
{

}

//base entities have no visual presence, but can if they have a texture
void BaseEntity::render(Application2D* appPtr)
{
	//the rotation occurs from the top-left corner
	//use another matrix to force entities to rotate from the centre
	Matrix3 correction = Matrix3{};
	correction.identity();
	correction[2][0] = baseTexture->getWidth() / -2.0f + centreOffset.x;
	correction[2][1] = baseTexture->getHeight() / -2.0f + centreOffset.y;

	appPtr->m_2dRenderer->drawSpriteTransformed3x3(baseTexture, collider->transform.globalTransform * correction, 0.0f, 0.0f, -1, 0.0f, 0.0f);
}
