#include "enemy_entity.h"
#include "Application2D.h"

//default value constructor
EnemyEntity::EnemyEntity(Application2D* appPtr, Path* path, PlayerEntity* player)
{
	type = EntityType::ENEMY;

	enemyTexture = appPtr->enemyTexture; //assign texture

	float width = (float)enemyTexture->getWidth();
	float height = (float)enemyTexture->getHeight();

	//set the radius of the collider to be the bigger of the width and height
	float radius = (width > height ? width : height) * 0.5f;

	Circle* hitcircle = new Circle{ radius };
	collider = hitcircle;

	mass = 1.0f;
	calculateMass(); //figures out the other mass-related variables based on regular mass

	inertia = 0.0f; //players do not rotate
	invInertia = 0.0f;

	friction = 0.0f; //no friction
	restitution = 0.0f; //no bounce

	//select a random place to spawn the entity at
	size_t connSize = player->closestNode->conns.size();
	int randNum = rand() % connSize;
	collider->transform.translation = player->closestNode->conns[randNum].destination->position;

	collider->layer = 0b10000;

	//set the target of the enemy
	target = player;
}

//gets called when the entity is involved in a collision
void EnemyEntity::collisionCallBack(BaseEntity * other)
{
}

//update, called once per frame
void EnemyEntity::update(float deltaTime, Application2D* appPtr)
{
	aie::Input* input = aie::Input::getInstance();

	Vector2 moveVec = Vector2{};

	//get closest node
	closestNode = getClosestNode(&appPtr->world, &appPtr->path);

	Line* playerLine = new Line{ collider->transform.translation, target->collider->transform.translation };
	playerLine->layer = 0b0100;
	bool canSeePlayer = appPtr->world.testCollider(playerLine).size() > 0;

	Vector2 relative;

	//get a path from the enemy to the player if the both know where they are
	if (closestNode != nullptr && target->closestNode != nullptr)
	{
		//calculate a path if there isn't one yet
		if (pathList.size() == 0)
		{
			pathList = appPtr->path.calculatePath(closestNode, target->closestNode);
		}

		//if the end point of the calculated path is the player's closest node
		if (pathList[0]->position == target->closestNode->position)
		{
			//is the relative distance from the enemy to the next node smaller than epsilon
			if ((pathList[pathList.size() - 1]->position - collider->transform.translation).sqrMagnitude() <= nodeEpsilon * nodeEpsilon)
			{
				pathList.pop_back();
			}

			if (pathList.size() == 0 && !canSeePlayer)
			{
				pathList = appPtr->path.calculatePath(closestNode, target->closestNode);
			}

			if (pathList.size() > 0)
			{
				relative = (pathList[pathList.size() - 1]->position - collider->transform.translation);
			}
		}
		else //recalculate path
		{
			pathList = appPtr->path.calculatePath(closestNode, target->closestNode);
		}
	}



	if (!canSeePlayer)
	{
		relative = (target->collider->transform.translation - collider->transform.translation);
	}

	delete playerLine;

	Vector2 relDir = relative.normalised();

	float contr = velocity.dot(relDir);
	contr = contr < 0 ? 0 : contr; //clamp to 0 or above

	Vector2 velRel = relDir * velocity.dot(relDir); //velocity along the relative direction of travel
	Vector2 tangent = velocity - velRel; //velocity that opposes this movement

	moveVec = (relative - tangent).normalised();

	velocity += moveVec * moveAcceleration * deltaTime;
	velocity = velocity * pow(moveFriction, deltaTime * 60.0f);

	angularVelocity = 0.0f;
}

//get the closest node that can be moved directly towards
Node * EnemyEntity::getClosestNode(SpatialPartition * world, Path * path)
{
	size_t nodeSize = path->nodes.size();

	Node* bestNode = nullptr;
	float bestSqrDist = std::numeric_limits<float>().max();

	for (size_t i = 0; i < nodeSize; i++)
	{
		Node* node = path->nodes[i];

		float sqrDist = (collider->transform.translation - node->position).sqrMagnitude();

		//test if the node is closer
		if (sqrDist < bestSqrDist)
		{
			bestNode = node;
			bestSqrDist = sqrDist;
		}
	}

	return bestNode;
}

//renders the enemy
void EnemyEntity::render(Application2D* appPtr)
{
	//the rotation occurs from the top-left corner
	//use another matrix to force entities to rotate from the centre
	Matrix3 correction = Matrix3{};
	correction.identity();
	correction[2][0] = enemyTexture->getWidth() / -2.0f;
	correction[2][1] = enemyTexture->getHeight() / -2.0f;

	appPtr->m_2dRenderer->drawSpriteTransformed3x3(enemyTexture, collider->transform.globalTransform * correction, 0.0f, 0.0f, 0, 0.0f, 0.0f);
}
