#include "collider.h"
#include "AABB.h"

//destructor, deletes the hull
Collider::~Collider()
{
	delete hull;
}
