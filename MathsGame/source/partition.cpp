#include "partition.h"
#include "AABB.h"
#include "physics.h"
#include "factory.h"

//constructor
SpatialPartition::SpatialPartition()
{

}

//destructor
SpatialPartition::~SpatialPartition()
{
	delete root;

	size_t entitiesSize = entities.size();

	for (size_t i = 0; i < entitiesSize; i++)
	{
		delete entities[i].entity;
	}
}

//initialise the partition
void SpatialPartition::initialisePartition()
{
	size_t iSize = nodes.size();

	for (size_t i = 0; i < iSize; i++)
	{
		size_t jSize = nodes[i].size();

		for (size_t j = 0; j < jSize; j++)
		{
			//erase each array of colliders (2 dimensions down)
			nodes[i][j].erase(nodes[i][j].begin(), nodes[i][j].end());
		}

		//erase each array 1 dimension down
		nodes[i].erase(nodes[i].begin(), nodes[i].end());
	}

	//erase each array
	nodes.erase(nodes.begin(), nodes.end());

	size_t newISize = iLength;
	size_t newJSize = jLength;

	for (size_t i = 0; i < newISize; i++)
	{
		std::vector<std::vector<BaseEntity*>> node2D;

		nodes.push_back(node2D);

		for (size_t j = 0; j < newJSize; j++)
		{
			std::vector<BaseEntity*> node1D;
			nodes[i].push_back(node1D);
		}
	}
}

//add collider to partition
bool SpatialPartition::registerCollider(BaseEntity* entity, bool full)
{
	entity->collider->transform.updateGlobalTransform();
	entity->collider->transform.updateChildren();

	if (entity->type == EntityType::SEAT)
	{
		int a = 0;
	}


	entity->collider->generateHull();
	AABB* hull = entity->collider->hull;

	Range xRange = Range{};
	Range yRange = Range{};

	xRange.min = hull->min.x;
	xRange.max = hull->max.x;

	yRange.min = hull->min.y;
	yRange.max = hull->max.y;


	float xSize = xRange.max - xRange.min;
	float ySize = yRange.max - yRange.min;

	//the collider is too big to be added to the partition
	if (xSize > nodeSize * 6.0f || ySize > nodeSize * 6.0f)
	{
		return false;
	}

	SpatialPartitionBodyPair partEntityPair;

	partEntityPair.entity = entity;

	//get the indices that the collider intersects
	float xStart = xRange.min - origin.x;
	xStart /= nodeSize;

	float xEnd = xRange.max - origin.x;
	xEnd /= nodeSize;

	float yStart = yRange.min - origin.y;
	yStart /= nodeSize;

	float yEnd = yRange.max - origin.y;
	yEnd /= nodeSize;

	std::vector<index2D> intersections;

	//round the iterators down
	xStart = floorf(xStart);
	xEnd = ceilf(xEnd);

	yStart = floorf(yStart);
	yEnd = ceilf(yEnd);

	//convert the ranges to index loops
	for (int i = (int)yStart; i <= (int)yEnd; i++)
	{
		for (int j = (int)xStart; j <= (int)xEnd; j++)
		{
			//test if the index is inside the partioned region
			if ((j >= 0 && j < jLength) && (i >= 0 && i < iLength))
			{
				index2D newIndex = index2D{};
				newIndex.i = i;
				newIndex.j = j;

				intersections.push_back(newIndex);
			}
		}
	}

	size_t interSize = intersections.size();

	//add the collider to the 2D partition array
	for (size_t i = 0; i < interSize; i++)
	{
		nodes[intersections[i].i][intersections[i].j].push_back(entity);
	}

	if (!full)
	{
		return true;
	}

	entities.push_back(partEntityPair);

	return true;
}

//remove collider from partition
void SpatialPartition::removeCollider(BaseEntity** entitydPtr, bool full, int id)
{
	BaseEntity* entityPtr = *entitydPtr;

	entityPtr->collider->generateHull();
	AABB* hull = entityPtr->collider->hull;

	Range xRange = Range{};
	Range yRange = Range{};

	xRange.min = hull->min.x;
	xRange.max = hull->max.x;

	yRange.min = hull->min.y;
	yRange.max = hull->max.y;

	float xSize = xRange.max - xRange.min;
	float ySize = yRange.max - yRange.min;

	SpatialPartitionBodyPair partEntityPair;

	partEntityPair.entity = entityPtr;

	//get the indices that the collider intersects
	float xStart = xRange.min - origin.x;
	xStart /= nodeSize;

	float xEnd = xRange.max - origin.x;
	xEnd /= nodeSize;

	float yStart = yRange.min - origin.y;
	yStart /= nodeSize;

	float yEnd = yRange.max - origin.y;
	yEnd /= nodeSize;

	std::vector<index2D> intersections;

	//round the iterators down
	xStart = floorf(xStart);
	xEnd = ceilf(xEnd);

	yStart = floorf(yStart);
	yEnd = ceilf(yEnd);

	//convert the ranges to index loops
	for (int i = (int)yStart; i <= (int)yEnd; i++)
	{
		for (int j = (int)xStart; j <= (int)xEnd; j++)
		{
			//test if the index is inside the partioned region
			if ((j >= 0 && j < jLength) && (i >= 0 && i < iLength))
			{
				index2D newIndex = index2D{};
				newIndex.i = i;
				newIndex.j = j;

				intersections.push_back(newIndex);
			}
		}
	}

	size_t interSize = intersections.size();

	//remove the collider from the 2D partition array
	for (size_t i = 0; i < interSize; i++)
	{
		size_t searchSize = nodes[intersections[i].i][intersections[i].j].size();
		std::vector<BaseEntity*> & node = nodes[intersections[i].i][intersections[i].j];

		for (size_t j = 0; j < searchSize; j++)
		{
			//find the entity in the array and erase
			if (entityPtr == node[j])
			{
				node.erase(node.begin() + j);
				searchSize--;
			}
		}

	}

	if (!full)
	{
		return;
	}

	size_t entitiesSize = entities.size();

	//remove the collider from the general array of all entities
	for (size_t i = 0; i < entitiesSize; i++)
	{
		if (entityPtr == entities[i].entity)
		{
			entities.erase(entities.begin() + i);
			break;
		}
	}

	delete entityPtr;
	(*entitydPtr) = nullptr;
	
}

//test a collider against the partition that isn't in the partition
std::vector<BaseEntity*> SpatialPartition::testCollider(Collider * collider)
{
	collider->transform.updateGlobalTransform();

	std::vector<BaseEntity*> collidees; //list that contains all of the colliding entities
	std::vector<BaseEntity*> neighbours = getNeighbours(collider);

	size_t neighSize = neighbours.size();

	//test for collision against all neighbours
	for (size_t j = 0; j < neighSize; j++)
	{
		BaseEntity* neighbour = neighbours[j];

		//other object is either sleeping or not recieving collisions
		if (!neighbour->colliding)
		{
			continue;
		}

		//the two objects don't belong to at least one common layer
		if ((collider->layer & neighbour->collider->layer) == 0)
		{
			continue;
		}

		SimpleCollision simpleColl = COLL_SOLVER->doAdvancedIntersectionTest(collider, neighbour->collider);

		if (simpleColl.intersection)
		{
			collidees.push_back(neighbour);
		}
	}

	return collidees;
}

//get the potential entities that could be colliding with the given collider
std::vector<BaseEntity*> SpatialPartition::getNeighbours(Collider * collider)
{
	collider->generateHull();
	AABB* hull = collider->hull;

	Range xRange = Range{};
	Range yRange = Range{};

	xRange.min = hull->min.x;
	xRange.max = hull->max.x;

	yRange.min = hull->min.y;
	yRange.max = hull->max.y;


	float xSize = xRange.max - xRange.min;
	float ySize = yRange.max - yRange.min;

	//get the indices that the collider intersects
	float xStart = xRange.min - origin.x;
	xStart /= nodeSize;

	float xEnd = xRange.max - origin.x;
	xEnd /= nodeSize;

	float yStart = yRange.min - origin.y;
	yStart /= nodeSize;

	float yEnd = yRange.max - origin.y;
	yEnd /= nodeSize;

	std::vector<index2D> intersections;

	//round the iterators down
	xStart = floorf(xStart);
	xEnd = ceilf(xEnd);

	yStart = floorf(yStart);
	yEnd = ceilf(yEnd);

	//convert the ranges to index loops
	for (int i = (int)yStart; i <= (int)yEnd; i++)
	{
		for (int j = (int)xStart; j <= (int)xEnd; j++)
		{
			//test if the index is inside the partioned region
			if ((j >= 0 && j < jLength) && (i >= 0 && i < iLength))
			{
				index2D newIndex = index2D{};
				newIndex.i = i;
				newIndex.j = j;

				intersections.push_back(newIndex);
			}
		}
	}

	size_t interSize = intersections.size();
	
	std::vector<BaseEntity*> neighbours;

	//remove the collider to the 2D partition array
	for (size_t i = 0; i < interSize; i++)
	{
		std::vector<BaseEntity*>* node = &nodes[intersections[i].i][intersections[i].j];
		size_t nodeSize = node->size();

		//add every collider from the node
		for (size_t j = 0; j < nodeSize; j++)
		{
			BaseEntity* neighbour = (*node)[j];

			//don't make a shape test collisions against itself
			if (neighbour->collider != collider)
			{
				neighbours.push_back(neighbour); 
			}
		}
	}

	return neighbours;
}

//get the potential entities that could be colliding with the given entity
std::vector<BaseEntity*> SpatialPartition::getNeighbours(BaseEntity * entity)
{

	entity->collider->generateHull();
	AABB* hull = entity->collider->hull;

	Range xRange = Range{};
	Range yRange = Range{};

	xRange.min = hull->min.x;
	xRange.max = hull->max.x;

	yRange.min = hull->min.y;
	yRange.max = hull->max.y;

	float xSize = xRange.max - xRange.min;
	float ySize = yRange.max - yRange.min;

	//get the indices that the collider intersects
	float xStart = xRange.min - origin.x;
	xStart /= nodeSize;

	float xEnd = xRange.max - origin.x;
	xEnd /= nodeSize;

	float yStart = yRange.min - origin.y;
	yStart /= nodeSize;

	float yEnd = yRange.max - origin.y;
	yEnd /= nodeSize;

	std::vector<index2D> intersections;

	//round the iterators down
	xStart = floorf(xStart);
	xEnd = ceilf(xEnd);

	yStart = floorf(yStart);
	yEnd = ceilf(yEnd);

	//convert the ranges to index loops
	for (int i = (int)yStart; i <= (int)yEnd; i++)
	{
		for (int j = (int)xStart; j <= (int)xEnd; j++)
		{
			//test if the index is inside the partioned region
			if ((j >= 0 && j < jLength) && (i >= 0 && i < iLength))
			{
				index2D newIndex = index2D{};
				newIndex.i = i;
				newIndex.j = j;

				intersections.push_back(newIndex);
			}
		}
	}

	size_t interSize = intersections.size();

	std::vector<BaseEntity*> neighbours;

	//remove the collider to the 2D partition array
	for (size_t i = 0; i < interSize; i++)
	{
		std::vector<BaseEntity*>* node = &nodes[intersections[i].i][intersections[i].j];
		size_t nodeSize = node->size();
		
		//add every collider from the node
		for (size_t j = 0; j < nodeSize; j++)
		{
			BaseEntity* neighbour = (*node)[j];

			//don't make a shape test collisions against itself
			if (neighbour != entity)
			{
				neighbours.push_back(neighbour);
			}
		}
	}

	return neighbours;
}

//update all of the colliders
void SpatialPartition::updateAll(float deltaTime, Application2D* appPtr)
{
	size_t entitiesSize = entities.size();

	//move every entity
	for (size_t i = 0; i < entitiesSize; i++)
	{
		BaseEntity* entity = entities[i].entity;

		entity->update(deltaTime, appPtr);

		//test if the entity got removed after it's update
		if (entitiesSize > entities.size())
		{
			entitiesSize = entities.size();
			i--;
			continue;
		}
		else if (entitiesSize < entities.size())
		{
			entitiesSize = entities.size();
			i++;
			continue;
		}

		//don't move static objects
		if (entity->invMass == 0 || !entity->awake)
		{
			continue;
		}

		//don't add the entity back if it was deleted during the update
		removeCollider(&entity, false, 1);

		entity->collider->transform.translation += entity->velocity * deltaTime;
		entity->collider->transform.rotation += entity->angularVelocity * deltaTime;

		//update the matrices, a change was made
		entity->collider->transform.updateGlobalTransform();
		entity->collider->transform.updateChildren();
		
		registerCollider(entity, false);

		if (entity->collider->transform.parent == nullptr)
		{
			entity->collider->transform.setParent(&root->collider->transform);
		}
	
	}

	entitiesSize = entities.size();

	//test all neighbours for collisions
	for (size_t i = 0; i < entitiesSize; i++)
	{
		BaseEntity* entity = entities[i].entity;

		//object is either sleeping or not recieving collisions
		if (!entity->awake || !entity->colliding || entity->invMass == 0)
		{
			continue;
		}

		std::vector<BaseEntity*> neighbours = getNeighbours(entity);

		size_t neighSize = neighbours.size();

		for (size_t j = 0; j < neighSize; j++)
		{
			
			BaseEntity* neighbour = neighbours[j];

			if (entity->type == EntityType::CAR && neighbour->type == EntityType::BASE)
			{
				int a = 0;
			}

			//the two objects don't belong to at least one common layer
			if ((entity->collider->layer & neighbour->collider->layer) == 0)
			{
				continue;
			}

			//other object is either sleeping or not recieving collisions
			if (!neighbour->awake || !neighbour->colliding)
			{
				continue;
			}

			float massSum = entity->mass + neighbour->mass;

			//static objects can't intersect
			if (massSum == 0)
			{
				continue;
			}

			AdvancedCollision advColl = COLL_SOLVER->doBaseEntityIntersectionTest(entity, neighbour, deltaTime);

			if (advColl.intersection)
			{
				
				//collision callback
				entity->collisionCallBack(neighbour);
				neighbour->collisionCallBack(entity);

				//are either of the two entities not reacting to collisions
				if (!entity->reactive || !neighbour->reactive)
				{
					continue;
				}

				float invMassSum = entity->invMass + neighbour->invMass;

				//solve the penetration using the MTV returned from the seperating axis theorem
				//apply the MTV using a ratio of the masses so that heavier objects move less when hit by larger ones
				float aRatio = entity->invMass / invMassSum;
				float bRatio = neighbour->invMass / invMassSum;

				if (entity->invMass > 0)
				{
					removeCollider(&entity, false, 2);
					entity->collider->transform.translation += advColl.MTV * -aRatio;

					//update the matrices, a change was made
					entity->collider->transform.updateGlobalTransform();
					entity->collider->transform.updateChildren();

					registerCollider(entity, false);
				}

				if (neighbour->invMass > 0)
				{
					removeCollider(&neighbour, false, 3);
					neighbour->collider->transform.translation += advColl.MTV * bRatio;

					//update the matrices, a change was made
					neighbour->collider->transform.updateGlobalTransform();
					neighbour->collider->transform.updateChildren();

					registerCollider(neighbour, false);
				}

				//calculate the contacts
				advColl = COLL_SOLVER->calculateContacts(advColl);

				//apply physics impulses to make the collision behave under the laws of physics
				PHYS_SOLVER->applyImpulse(advColl);
			}
		}
	}
}

//render every entity contained by the partition
void SpatialPartition::renderAll(Application2D* appPtr)
{
	size_t entitiesSize = entities.size();

	//render every entity
	for (size_t i = 0; i < entitiesSize; i++)
	{
		entities[i].entity->render(appPtr);
	}
}
