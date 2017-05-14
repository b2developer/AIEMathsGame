#include "point.h"

#include "Application2D.h"
#include "AABB.h"

//sets the position of the point
Point::Point(Vector2 _position)
{
	colliderType = BoundsType::POINT;
	position = _position;
}

//dot product of the point
Range Point::project(Vector2 axis)
{

	//transform the point
	Vector2 positionTra = (Vector3(position.x, position.y, 1) * transform.globalTransform).GetXY();

	//normalise the axis
	Vector2 axisNorm = axis.normalised();

	float dot = axisNorm.dot(positionTra);

	Range best = {};

	//only one dot product, it is the minumum dot and maximum dot
	best.min = dot;
	best.max = dot;

	return best;
}

std::vector<Vector2> Point::getPoints()
{
	return std::vector<Vector2>{position};
}

//closest point in any given direction for a point is itself
std::vector<Vector2> Point::support(Vector2 normal)
{
	//get the global transformation matrix without translation
	Matrix3 globalInvTrans = transform.globalTransform;
	globalInvTrans.setTranslate(Vector2{ 0,0 });

	return std::vector<Vector2>{globalInvTrans * (Vector3)position};
}

float Point::momentOfInertia(float mass)
{
	return mass * position.sqrMagnitude();
}

//create an aabb that encapsulates the shape
void Point::generateHull()
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

//render the point
void Point::render(Application2D* app)
{
	//transform the point
	Vector2 positionTra = (transform.globalTransform * Vector3(position.x, position.y, 1)).GetXY();

	app->m_2dRenderer->drawCircle(positionTra.x, positionTra.y, 5.0f, 0.0f);
}
