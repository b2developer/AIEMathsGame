#include "collision.h"
#include <vector>
#include <limits>
#include <typeinfo>

//get a pointer to the singleton
CollisionSolver* CollisionSolver::getInstance()
{
	//is defined at the start of the program
	static CollisionSolver* singleton = nullptr;

	//if the pointer contains no instance, assign one
	if (singleton == nullptr)
	{
		singleton = new CollisionSolver();
	}

	return singleton;
}

//invokes doAdvancedIntersectionTest and returns whether the collision occured or not
bool CollisionSolver::doSimpleIntersectionTest(Collider* A, Collider* B)
{
	return doAdvancedIntersectionTest(A, B).intersection;
}

//tests if two shapes are intersecting using the seperating axis theorem
SimpleCollision CollisionSolver::doAdvancedIntersectionTest(Collider * A, Collider * B)
{
	std::vector<Vector2> axes;

	//get the axes from each shape to test
	std::vector<Vector2> A_axes = A->getAxes(*B);
	std::vector<Vector2> B_axes = B->getAxes(*A);

	//add A's axes to test to the common list
	axes.insert(axes.end(), A_axes.begin(), A_axes.end());

	//add B's axes to test to the common list
	axes.insert(axes.end(), B_axes.begin(), B_axes.end());

	size_t size = axes.size();

	Vector2 bestAxis = Vector2{};
	float smallestPenetration = std::numeric_limits<float>().max();

	for (size_t i = 0; i < size; i++)
	{
		//get the smallest and largest dot products of the shapes
		Range A_proj = A->project(axes[i]);
		Range B_proj = B->project(axes[i]);
		 
		//test if the ranges overlap
		if (A_proj.min <= B_proj.max && B_proj.min <= A_proj.max)
		{
			//calculate smallest penetration from ranges
			float p1 = B_proj.max - A_proj.min;
			float p2 = A_proj.max - B_proj.min;

			//get the smallest value
			float penetration = abs(p1) < abs(p2) ? p1 : p2;

			//test if it is smaller than the smallest global penetration
			if (abs(penetration) < abs(smallestPenetration))
			{
				bestAxis = axes[i];
				smallestPenetration = penetration;

				if (A_proj.min > B_proj.min)
				{
					smallestPenetration *= -1.0f;
				}
			}

		}
		else
		{
			//bail out, a seperating axis was found
			SimpleCollision fail;
			fail.A = A;
			fail.B = B;
			fail.intersection = false;
			fail.MTV = Vector2{};
			return fail;
		}
	}

	//collision occured, return the collision information
	SimpleCollision success;
	success.A = A;
	success.B = B;
	success.intersection = true;
	success.MTV = bestAxis * smallestPenetration;
	return success;
}

//tests if two bodies are intersecting using the seperating axis theorem and returns detailed information about the collision
AdvancedCollision CollisionSolver::doBaseEntityIntersectionTest(BaseEntity * A, BaseEntity * B, float deltaTime)
{
	std::vector<Vector2> axes;
	std::vector<float> penetrations;

	//get the axes from each shape to test
	std::vector<Vector2> A_axes = A->collider->getAxes(*B->collider);
	std::vector<Vector2> B_axes = B->collider->getAxes(*A->collider);

	//add A's axes to test to the common list
	axes.insert(axes.end(), A_axes.begin(), A_axes.end());

	//add B's axes to test to the common list
	axes.insert(axes.end(), B_axes.begin(), B_axes.end());

	size_t size = axes.size();

	Vector2 bestAxis = Vector2{};
	float smallestPenetration = std::numeric_limits<float>().max();

	Vector2 A_bestAxis = Vector2{};
	float A_smallestPenetration = std::numeric_limits<float>().max();

	Vector2 B_bestAxis = Vector2{};
	float B_smallestPenetration = std::numeric_limits<float>().max();

	size_t bSize = B_axes.size();

	for (size_t i = 0; i < size; i++)
	{
		//get the smallest and largest dot products of the shapes
		Range A_proj = A->collider->project(axes[i]);
		Range B_proj = B->collider->project(axes[i]);

		//test if the ranges overlap
		if (A_proj.min <= B_proj.max && B_proj.min <= A_proj.max)
		{
			//calculate smallest penetration from ranges
			float p1 = B_proj.max - A_proj.min;
			float p2 = A_proj.max - B_proj.min;

			//get the smallest value
			float penetration = abs(p1) < abs(p2) ? p1 : p2;

			penetrations.push_back(penetration);

			//test if it is smaller than the smallest global penetration
			if (abs(penetration) < abs(smallestPenetration))
			{
				bestAxis = axes[i];
				smallestPenetration = penetration;

				//reverse the penetration, the range calculation is the wrong way around
				if (A_proj.min > B_proj.min)
				{
					smallestPenetration *= -1.0f;
				}
			}

			//test if it is smaller than A's smallest penetration
			if (abs(penetration) < abs(A_smallestPenetration) && i < size - bSize)
			{
				A_bestAxis = axes[i];
				A_smallestPenetration = penetration;

				//reverse the penetration, the range calculation is the wrong way around
				if (A_proj.min > B_proj.min)
				{
					A_smallestPenetration *= -1.0f;
				}
			}

			//test if it is smaller than A's smallest penetration
			if (abs(penetration) < abs(B_smallestPenetration) && i >= size - bSize)
			{
				B_bestAxis = axes[i];
				B_smallestPenetration = penetration;

				//reverse the penetration, the range calculation is the wrong way around
				if (A_proj.min > B_proj.min)
				{
					B_smallestPenetration *= -1.0f;
				}
			}


		}
		else
		{
			//bail out, a seperating axis was found
			AdvancedCollision fail;
			fail.A = A;
			fail.B = B;
			fail.intersection = false;
			fail.MTV = Vector2{};
			return fail;
		}
	}


	//collision occured, return the collision information
	AdvancedCollision success;
	success.A = A;
	success.B = B;
	success.MTV = bestAxis * smallestPenetration;
	success.normal = success.MTV.normalised();
	success.intersection = true;

	return success;
}

//calculates the contact point relative to the two shapes
AdvancedCollision CollisionSolver::calculateContacts(AdvancedCollision partial)
{

	if (partial.A->invMass + partial.B->invMass > 0)
	{
		int a = 0;
	}

	Vector2 normal = partial.MTV.normalised();

	std::vector<Vector2> A_supports = partial.A->collider->support(normal);
	std::vector<Vector2> B_supports = partial.B->collider->support(normal * -1.0f);

	Matrix3 A_globalMatrix = partial.A->collider->transform.globalTransform;
	Matrix3 B_globalMatrix = partial.B->collider->transform.globalTransform;
	
	//get the positions with transformations
	Vector2 A_position = Vector2{ A_globalMatrix[2][0], A_globalMatrix[2][1] };
	Vector2 B_position = Vector2{ B_globalMatrix[2][0], B_globalMatrix[2][1] };

	if (A_supports.size() == 1)
	{
		//get the contact points relative to A
		partial.A_contact = A_supports[0];
		partial.B_contact = (A_position + partial.A_contact) - B_position;

	}
	else if (B_supports.size() == 1)
	{
		//get the contact points relative to B
		partial.B_contact = B_supports[0];
		partial.A_contact = (B_position + partial.B_contact) - A_position;
	}
	else
	{
		//get the contact points from averages
		Vector2 average = Vector2{};

		size_t supportSize = A_supports.size();

		for (size_t i = 0; i < supportSize; i++)
		{
			average += A_supports[i];
		}

		average = average / (float)supportSize;

		partial.A_contact = average;

	    average = Vector2{};

	    supportSize = B_supports.size();

		for (size_t i = 0; i < supportSize; i++)
		{
			average += B_supports[i];
		}

		average = average / (float)supportSize;

		partial.B_contact = average;
	}

	return partial;

}