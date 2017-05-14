#include "player_entity.h"
#include "factory.h"
#include "projectile_entity.h"
#include "Application2D.h"

//default value constructor
PlayerEntity::PlayerEntity(Application2D* appPtr, Path* path)
{
	type = EntityType::PLAYER;

	playerTexture = appPtr->playerTexture; //assign texture

	float width = (float)playerTexture->getWidth();
	float height = (float)playerTexture->getHeight();

	//set the radius of the collider to be the bigger of the width and height
	float radius = (width > height ? width : height) * 0.5f;

	Circle* hitcircle = new Circle{ radius };
	collider = hitcircle;

	mass = 1.0f;
	calculateMass(); //figures out the other mass-related variables based on regular mass

	inertia = 0.0f; //players do not rotate
	invInertia = 0.0f;

	friction = 0.001f; //tiny amounts of friction
	restitution = 0.0f; //no bounce

	//spawn the entity at the centre of the world
	collider->transform.translation = path->nodes[0]->position;

	collider->layer = 0b10010;

	//set the offsets of the weapons
	primaryWeaponOffset = Vector2{ 20,0 };
	secondaryWeaponOffset = Vector2{ -20,0 };
}

//gets called when the entity is involved in a collision
void PlayerEntity::collisionCallBack(BaseEntity * other)
{
	//is the other entity a weapon
	if (other->type == EntityType::WEAPON)
	{
		//is the weapon not the primary or secondary
		if (primaryWeapon != other || secondaryWeapon != other)
		{
			collidedWeapon = (WeaponEntity*)other;
		}
	}
}

//operates using fetched input from an Application2D
void PlayerEntity::update(float deltaTime, Application2D* appPtr)
{

	aie::Input* input = aie::Input::getInstance();

	Vector2 inputVec = Vector2{};

	//if not parented
	if (collider->transform.parent == &appPtr->root->collider->transform)
	{
		//accelerate the player
		if (input->isKeyDown(aie::INPUT_KEY_W))
		{
			inputVec.y += 1.0f;
		}

		//accelerate the player
		if (input->isKeyDown(aie::INPUT_KEY_S))
		{
			inputVec.y -= 1.0f;
		}

		//accelerate the player
		if (input->isKeyDown(aie::INPUT_KEY_A))
		{
			inputVec.x -= 1.0f;
		}

		//accelerate the player
		if (input->isKeyDown(aie::INPUT_KEY_D))
		{
			inputVec.x += 1.0f;
		}
	}

	//make the player look at the mouse, even when parented to other entities
	//-------------------------------------------------------------------------
	//get the direction that the projectile was fired in
	Vector2 mouse = Vector2{ (float)input->getMouseX(), (float)input->getMouseY() };
	Vector2 mousePos = appPtr->m_camera + mouse;

	Matrix3 globalMatrix = collider->transform.globalTransform;

	Vector2 relDir = (mousePos - Vector2{ globalMatrix[2][0], globalMatrix[2][1] }).normalised();

	Matrix3 invRotation;
	invRotation.identity();

	float rotation = 0;

	if (collider->transform.parent != nullptr)
	{
		Vector2 rotationTarget = (Vector3{ 0,1,0 } * collider->transform.parent->globalTransform);
		invRotation.setRotateZ(-rotationTarget.getRotation());
	}

	//get a rotation matrix pointing towards the mouse
	Matrix3 mouseRotation;
	mouseRotation.setRotateZ(relDir.getRotation());

	Vector2 rotationTarget = (Vector3{ 0,1,0 } * (mouseRotation * invRotation));

	collider->transform.rotation = rotationTarget.getRotation() - PI / 2.0f;
	//-------------------------------------------------------------------------

	//if left click
	if (input->isMouseButtonDown(0))
	{
		//fire the secondary weapon if it exists
		if (secondaryWeapon != nullptr)
		{
			secondaryWeapon->fire(appPtr);
		}
	}

	//if right click
	if (input->isMouseButtonDown(1))
	{
		//fire the primary weapon if it exists
		if (primaryWeapon != nullptr) 
		{
			primaryWeapon->fire(appPtr);
		}
	}

	//if left shift is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT_SHIFT))
	{

		//test the position of the click for a car
		Circle click = Circle{ 5.0f };
		click.transform.translation = mousePos;

		std::vector<BaseEntity*> collidees = appPtr->world.testCollider(&click);

		size_t collSize = collidees.size();

		//if one of the entities collided with was a car, memorise it with a pointer
		for (size_t i = 0; i < collSize; i++)
		{
			if (collidees[i]->type == EntityType::SEAT)
			{
				collidedSeat = (SeatEntity*)collidees[i];
				break;
			}
			if (collidees[i]->type == EntityType::MOUNT)
			{
				collidedMount = (MountEntity*)collidees[i];
				break;
			}
		}
		
		if (collidedMount != nullptr && collidedMount->mounted == nullptr && (primaryWeapon != nullptr || secondaryWeapon != nullptr)) //is the user trying to interact with a mount
		{
			if (secondaryWeapon != nullptr) //place the secondary weapon in the mount
			{
				secondaryWeapon->toggleEquip(this);
				collidedMount->attachWeapon(secondaryWeapon);
				secondaryWeapon = nullptr;
				
			}
			else //place the primary weapon in the mount
			{
				primaryWeapon->toggleEquip(this);
				collidedMount->attachWeapon(primaryWeapon);
				primaryWeapon = nullptr;
				
			}
		
		}
		else if (collidedMount != nullptr && collidedMount->mounted != nullptr) //is there already a weapon attached
		{
			collidedMount->deattachWeapon();
		}
		else if (seat != nullptr) //is the user trying to get out of a seat
		{ 
			awake = true;
			colliding = true;
			seat->exitSeat();

			seat = nullptr;
		}
		else if (collidedSeat != nullptr) //is the user trying to get into a seat
		{
			awake = false;
			colliding = false;
			collidedSeat->enterSeat(this);

			seat = collidedSeat;
			collider->transform.translation = Vector2{ 0,0 }; //centre the position
		}
		else if (secondaryWeapon != nullptr) //is the user trying to drop the secondary
		{
			secondaryWeapon->toggleEquip(this); //drop the currently held secondary weapon
			secondaryWeapon = nullptr;
		}
		else if (collidedWeapon != nullptr) //is the user trying to pickup a weapon
		{
			collidedWeapon->toggleEquip(this); //pick up the weapon under the player
		  
			if (primaryWeapon == nullptr) //is the user trying to pickup a primary of secondary
			{
				primaryWeapon = collidedWeapon;
			}
			else
			{
				secondaryWeapon = collidedWeapon;
			}
		}
		else if (primaryWeapon != nullptr) //is the user trying to drop the primary weapon
		{
			primaryWeapon->toggleEquip(this); //drop the currently held primary weapon
			primaryWeapon = nullptr;
		}
		
	}

	//if not parented
	if (collider->transform.parent == &appPtr->root->collider->transform)
	{
		inputVec.normalise();

		velocity += inputVec * moveAcceleration * deltaTime;
		velocity = velocity * pow(moveFriction, deltaTime * 60.0f);
	}

	angularVelocity = 0.0f;

	collidedMount = nullptr;
	collidedSeat = nullptr;
	collidedWeapon = nullptr;
}

//get the closest node that can be moved directly towards
Node * PlayerEntity::getClosestNode(SpatialPartition * world, Path * path)
{
	size_t nodeSize = path->nodes.size();

	Node* bestNode = nullptr;
	float bestSqrDist = std::numeric_limits<float>().max();

	for (size_t i = 0; i < nodeSize; i++)
	{
		Node* node = path->nodes[i];

		//get a line between the centre of the entity and the node
		Line cast = Line{ collider->transform.translation, node->position };

		cast.layer = 0b0100;

		//consider the new node if a line can be drawn to it
		if (world->testCollider(&cast).size() == 0)
		{
			float sqrDist = (collider->transform.translation - node->position).sqrMagnitude();

			//test if the node is closer
			if (sqrDist < bestSqrDist)
			{
				bestNode = node;
				bestSqrDist = sqrDist;
			}
		}
	}

	return bestNode;
}

//renders the player
void PlayerEntity::render(Application2D* appPtr)
{
	//the rotation occurs from the top-left corner
	//use another matrix to force entities to rotate from the centre
	Matrix3 correction = Matrix3{};
	correction.identity();
	correction[2][0] = playerTexture->getWidth() / -2.0f;
	correction[2][1] = playerTexture->getHeight() / -2.0f;

	appPtr->m_2dRenderer->drawSpriteTransformed3x3(playerTexture, collider->transform.globalTransform * correction, 0.0f, 0.0f, -0.9f, 0.0f, 0.0f);
}
