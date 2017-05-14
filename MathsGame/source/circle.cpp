#include "circle.h"

#include "Application2D.h"
#include "AABB.h"

//sets the radius
Circle::Circle(float _radius)
{
	colliderType = BoundsType::CIRCLE;
	radius = _radius;
}

//gets the projection axis to use with a circle
std::vector<Vector2> Circle::getAxes(Collider& other)
{

	//get the positions with transformations
	Vector2 position = (Vector3{ 0,0,1 } * transform.globalTransform).GetXY();

	Vector2 closestAxis = Vector2{};
	float closestDistance = std::numeric_limits<float>().max();

	std::vector<Vector2> points = other.getPoints();

 	size_t size = points.size();

	//get the closest point to the centre of the circle 
	for (size_t i = 0; i < size; i++)
	{
		Vector2 pointTra = (Vector3{ points[i].x, points[i].y, 1 } * other.transform.globalTransform).GetXY();
		Vector2 axis = (pointTra - position);
		float sqrMag = axis.sqrMagnitude();

		if (sqrMag < closestDistance)
		{
			axis.normalise();
			closestAxis = axis;
			closestDistance = sqrMag;
		}
	}
	
	return std::vector<Vector2>{closestAxis};
}

//get the smallest and largest dot products of the circle to the axis
Range Circle::project(Vector2 axis)
{

	//get the positions with transformations
	Vector2 position = (Vector3{ 0,0,1 } * transform.globalTransform).GetXY();
	Vector2 axisNorm = axis.normalised();
	
	//get the projection positions
	Vector2 min = position - axisNorm * radius;
	Vector2 max = position + axisNorm * radius;

	//dot product of the two ends
	float startDot = axisNorm.dot(min);
	float endDot = axisNorm.dot(max);

	Range best = {};

	//sets the range so that the minimum dot product is always the minimum
	best.min = startDot < endDot ? startDot : endDot;
	best.max = startDot > endDot ? startDot : endDot;

	return best;
}

std::vector<Vector2> Circle::getPoints()
{
	return std::vector<Vector2>{Vector2{ 0,0 }};
}

//get the furthest point in a given direction
std::vector<Vector2> Circle::support(Vector2 normal)
{
	return std::vector<Vector2>{normal * radius};
}

//rotational mass calculation
float Circle::momentOfInertia(float mass)
{
	return mass * radius * radius;
}

//create an aabb
void Circle::generateHull()
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

//render the circle
void Circle::render(Application2D* app)
{
	Vector2 position = (transform.globalTransform * Vector3{ 0,0, 1 }).GetXY();

	app->m_2dRenderer->drawCircle(position.x, position.y, radius, 0.0f);

	app->m_2dRenderer->setRenderColour(1, 1, 1);
	app->m_2dRenderer->drawLine(position.x, position.y, (transform.globalTransform * Vector3{ 0, radius, 1 }).x, (transform.globalTransform * Vector3{ 0, radius , 1 }).y);
}
