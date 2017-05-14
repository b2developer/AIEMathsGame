#include "line.h"

#include "Application2D.h"
#include "AABB.h"

//sets the starting point and the ending point
Line::Line(Vector2 _start, Vector2 _end)
{
	colliderType = BoundsType::LINE;
	start = _start;
	end = _end;
}

//gets the projection axis of the line
std::vector<Vector2> Line::getAxes(Collider& other)
{

	//get the global transformation matrix without translation
	Matrix3 globalInvTrans = transform.globalTransform;
	globalInvTrans[2][0] = 0;
	globalInvTrans[2][1] = 0;

	//get the two ends by applying transformation
	Vector2 startTra = (Vector3(start.x, start.y, 1) * globalInvTrans).GetXY();
	Vector2 endTra = (Vector3(end.x, end.y, 1) * globalInvTrans).GetXY();

	std::vector<Vector2> axes;

	//adds the relative 'normal' vector from the start to the end of the line
	Vector2 normal = (endTra - startTra).normalised().normal();
	axes.push_back(normal);

	return axes;
}

//get the smallest and largest dot products of the circle to the axis
Range Line::project(Vector2 axis)
{

	//get the two ends by applying transformation
	Vector2 startTra = (Vector3(start.x, start.y, 1) * transform.globalTransform).GetXY();
	Vector2 endTra = (Vector3(end.x, end.y, 1) * transform.globalTransform).GetXY();

	Vector2 axisNorm = axis.normalised();

	//dot product of the two ends
	float startDot = axisNorm.dot(startTra);
	float endDot = axisNorm.dot(endTra);

	Range best = {};

	//sets the range so that the minimum dot product is always the minimum
	best.min = startDot < endDot ? startDot : endDot;
	best.max = startDot > endDot ? startDot : endDot;

	return best;

}

std::vector<Vector2> Line::getPoints()
{
	return std::vector<Vector2>{start, end};
}


//get furthest point/s in a given direction
std::vector<Vector2> Line::support(Vector2 normal)
{
	float startDot = start.normalised().dot(normal);
	float endDot = end.normalised().dot(normal);

	//if the start dot is a bigger than end dot, ignoring a small margin
	if (startDot > endDot + EPSILON)
	{
		return std::vector<Vector2>{start};
	}
	//if the end dot is a bigger than start dot, ignoring a small margin
	else if (endDot < startDot - EPSILON)
	{
		return std::vector<Vector2>{start};
	}
	else //start dot and end dot are basically the same
	{
		return std::vector<Vector2>{start, end};
	}
}

//rotational mass calculation
float Line::momentOfInertia(float mass)
{
	std::vector<Vector2> points = getPoints();

	float bestSqr = 0.0f;

	for (size_t i = 0; i < 2; i++)
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
void Line::generateHull()
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

//render the line
void Line::render(Application2D* app)
{

	//transform the start and end points
	Vector2 startTra = (transform.globalTransform * Vector3(start.x, start.y, 1)).GetXY();
	Vector2 endTra = (transform.globalTransform * Vector3(end.x, end.y, 1)).GetXY();

	app->m_2dRenderer->drawLine(startTra.x, startTra.y, endTra.x, endTra.y, 1.0f, 0.0f);
}
