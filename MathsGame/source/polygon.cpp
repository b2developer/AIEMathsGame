#include "polygon.h"

#include "Application2D.h"
#include "AABB.h"
#include <limits.h>

//sets the points container 
Polygon::Polygon(std::vector<Vector2> _points)
{
	colliderType = BoundsType::POLYGON;
	points = _points;
}

//gets all of the projection axes of the polygon
std::vector<Vector2> Polygon::getAxes(Collider& other)
{

	std::vector<Vector2> axes;

	size_t size = points.size();
	for (size_t i = 0; i < size; i++)
	{
		Vector2 nextTra = (Vector3(points[(i + 1) % size].x, points[(i + 1) % size].y, 1) * transform.globalTransform).GetXY();
		Vector2 currentTra = (Vector3(points[i].x, points[i].y, 1) * transform.globalTransform).GetXY();

		//get the normal vector of the side formed by two points
		Vector2 normal = (nextTra - currentTra).normalised().normal(NormalDirection::LEFT);
		axes.push_back(normal);
	}

	return axes;
}

//get the smallest and largest dot products of the polygon to the axis
Range Polygon::project(Vector2 axis)
{

	std::vector<Vector2> axes;

	size_t size = points.size();
	for (size_t i = 0; i < size; i++)
	{
		Vector2 pointTra = (Vector3(points[i].x, points[i].y, 1) * transform.globalTransform).GetXY();
		axes.push_back(pointTra);
	}

	Vector2 axisNorm = axis.normalised();

	Range best = {};

	//loop through all the points, get the smallest and largest products
	for (size_t i = 0; i < size; i++)
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

std::vector<Vector2> Polygon::getPoints()
{
	std::vector<Vector2> list;

	size_t size = points.size();
	for (size_t i = 0; i < size; i++)
	{
		list.push_back(Vector2(points[i].x, points[i].y));
	}

	return list;
}

//get furthest point/s in a given direction
std::vector<Vector2> Polygon::support(Vector2 normal)
{
	//get the global transformation matrix without translation
	Matrix3 globalInvTrans = transform.globalTransform;
	globalInvTrans[2][0] = 0;
	globalInvTrans[2][1] = 0;

	std::vector<Vector2> axes;

	size_t size = points.size();
	for (size_t i = 0; i < size; i++)
	{
		Vector2 pointTra = (Vector3(points[i].x, points[i].y, 1) * globalInvTrans).GetXY();
		axes.push_back(pointTra);
	}

	std::vector<Vector2> bestList;
	float bestDot = -1.1f; //this is not possible with normal dots, will get assigned over in the future

	for (size_t i = 0; i < size; i++)
	{
		float dot = axes[i].normalised().dot(normal);

		if (dot > bestDot)
		{
			//erase the list
			bestList.erase(bestList.begin(), bestList.end());
			bestDot = dot;
			bestList.push_back(axes[i]);
		}
		else if (abs(bestDot - dot) < EPSILON) //if the dots are basically the same
		{
			//add it to the list
			bestList.push_back(axes[i]);
		}
	}

	return bestList;

}

//rotational mass calculation
float Polygon::momentOfInertia(float mass)
{
	std::vector<Vector2> points = getPoints();

	float bestSqr = 0.0f;

	size_t size = points.size();

	for (size_t i = 0; i < size; i++)
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
void Polygon::generateHull()
{
	if (hull != nullptr)
	{
		delete hull;
	}

	Range xRange = project(Vector2{ 1,0 });
	Range yRange = project(Vector2{ 0,1 });

	Vector2 min = Vector2{ xRange.min, yRange.min };
	Vector2 max = Vector2{ xRange.max, yRange.max };

	hull = new AABB{ min, max };
}

//render the shape
void Polygon::render(Application2D* app)
{

	size_t size = points.size();

	//draw lines connecting all of the points
	for (size_t i = 0; i < size; i++)
	{
		Vector2 point1Tra = (transform.globalTransform * Vector3(points[i].x ,points[i].y, 1)).GetXY();
		Vector2 point2Tra = (transform.globalTransform * Vector3(points[(i + 1) % size].x, points[(i + 1) % size].y, 1)).GetXY();

		app->m_2dRenderer->drawLine(point1Tra.x, point1Tra.y, point2Tra.x, point2Tra.y, 1.0f, 0.0f);
	}
}
