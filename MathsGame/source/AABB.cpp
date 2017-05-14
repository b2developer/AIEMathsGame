#include "AABB.h"
#include "Application2D.h"

//sets the top-left corner and the bottom-right corner
AABB::AABB(Vector2 _min, Vector2 _max)
{
	colliderType = BoundsType::AABB;
	min = _min;
	max = _max;
}

//gets the four projection axes to use with a AABB
std::vector<Vector2> AABB::getAxes(Collider& other)
{

	//get the four corner positions with transformations
	Vector2 topLeft = (Vector3(min.x, min.y, 1) * transform.globalTransform).GetXY();
	Vector2 topRight = (Vector3(max.x, min.y, 1) * transform.globalTransform).GetXY();
	Vector2 bottomLeft = (Vector3(min.x, max.y, 1) * transform.globalTransform).GetXY();
	Vector2 bottomRight = (Vector3(max.x, max.y, 1) * transform.globalTransform).GetXY();
	
	std::vector<Vector2> axes;

	//add all relative vectors on the boundary of the AABB
	axes.push_back((topRight - topLeft).normalised());
	axes.push_back((bottomRight - topRight).normalised());
	axes.push_back((bottomLeft - bottomRight).normalised());
	axes.push_back((topLeft - bottomLeft).normalised());

	return axes;
}

//get the smallest and largest dot products of the AABB to the axis
Range AABB::project(Vector2 axis)
{

	//get the four corner positions with transformations
	Vector2 topLeft = (Vector3(min.x, min.y, 1) * transform.globalTransform).GetXY();
	Vector2 topRight = (Vector3(max.x, min.y, 1) * transform.globalTransform).GetXY();
	Vector2 bottomLeft = (Vector3(min.x, max.y, 1) * transform.globalTransform).GetXY();
	Vector2 bottomRight = (Vector3(max.x, max.y, 1) * transform.globalTransform).GetXY();

	std::vector<Vector2> axes;

	//add all corner vectors of the AABB
	axes.push_back(topLeft);
	axes.push_back(topRight);
	axes.push_back(bottomLeft);
	axes.push_back(bottomRight);
	
	Vector2 axisNorm = axis.normalised();

	Range best = {};

	//loop through the four points, get the smallest and largest products
	for (int i = 0; i < 4; i++)
	{
		float dot = axes[i].dot(axisNorm);

		if (dot < best.min)
		{
			best.min = dot;
		}
		if (dot > best.max)
		{
			best.max = dot;
		}
	}

	return best;
	
}

std::vector<Vector2> AABB::getPoints()
{
	return std::vector<Vector2>{Vector2{ min.x, min.y }, Vector2{ max.x, min.y }, Vector2{ min.x, max.y }, Vector2{ max.x, max.y }};
}

std::vector<Vector2> AABB::support(Vector2 normal)
{
	//get the global transformation matrix without translation
	Matrix3 globalInvTrans = transform.globalTransform;
	globalInvTrans[2][0] = 0;
	globalInvTrans[2][1] = 0;

	//get the four corner positions with transformations
	Vector2 topLeft = (Vector3(min.x, min.y, 1) * globalInvTrans).GetXY();
	Vector2 topRight = (Vector3(max.x, min.y, 1) * globalInvTrans).GetXY();
	Vector2 bottomLeft = (Vector3(min.x, max.y, 1) * globalInvTrans).GetXY();
	Vector2 bottomRight = (Vector3(max.x, max.y, 1) * globalInvTrans).GetXY();

	std::vector<Vector2> points;

	//add all corner vectors of the AABB
	points.push_back(topLeft);
	points.push_back(topRight);
	points.push_back(bottomLeft);
	points.push_back(bottomRight);

	std::vector<Vector2> bestList;
	float bestDot = -1.1f; //this is not possible with normal dots, will get assigned over in the future

	for (size_t i = 0; i < 4; i++)
	{
		float dot = points[i].normalised().dot(normal);

		if (dot > bestDot)
		{
			//erase the list
			bestList.erase(bestList.begin(), bestList.end());
			bestDot = dot;
			bestList.push_back(points[i]);
		}
		else if (abs(bestDot - dot) < EPSILON) //if the dots are basically the same
		{
			//add it to the list
			bestList.push_back(points[i]);
		}
	}

	return bestList;
}

//rotational mass calculation
float AABB::momentOfInertia(float mass)
{

	std::vector<Vector2> points = getPoints();

	float bestSqr = 0.0f;

	for (size_t i = 0; i < 4; i++)
	{
		float sqr = points[i].sqrMagnitude();

		if (bestSqr < sqr)
		{
			bestSqr = sqr;
		}
	}

	return mass * bestSqr;

}

//create an aabb that encapsulates the shape
void AABB::generateHull()
{
	if (hull != nullptr)
	{
		delete hull;
	}

	Range xRange = project(Vector2{ 1,0 });
	Range yRange = project(Vector2{ 0,1 });

	Vector2 min = Vector2{ xRange.min, yRange.min };
	Vector2 max = Vector2{ xRange.max, yRange.max };

	hull = new AABB{min, max};
}

void AABB::render(Application2D* app)
{

	//get the position and rotation from the matrix
	Vector2 position = (transform.globalTransform * Vector3{ 0, 0, 1 }).GetXY();

	Transform extraction = extractMatrix(transform.globalTransform);

	app->m_2dRenderer->drawBox(position.x, position.y, (max.x - min.x) * extraction.scale.x, (max.y - min.y) * extraction.scale.y, extraction.rotation);
}
