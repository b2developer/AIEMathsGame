#pragma once
#include "collider.h"

/*
* class Point
* child class of Collider
*
* a point that can be tested for intersection with other shapes
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Point : public Collider
{
public:

	//the point's location
	Vector2 position = { 0,0 };

	/*
	* Point()
	* default constructor
	*/
	Point() { colliderType = BoundsType::POINT; };

	/*
	* Point(Vector2, Vector2)
	* constructor - immediately sets the Point's position
	*
	* @param Vector2 - the position
	*/
	Point(Vector2);

	/*
	* ~Point()
	* default constructor
	*/
	~Point() {};

	/*
	* getAxes
	* overrides Collider's getAxes()
	*
	* calculates the axis to test with a Point
	*
	* @param Collider& other - the other shape in the collision test, this is necessary for circles
	* @returns std::vector<Vector2> - an empty vector, a point has no axes to test
	*/
	std::vector<Vector2> getAxes(Collider& other) override {
		return std::vector<Vector2>{};
	}

	/*
	* project
	* overrides Collider's project()
	*
	* calculates the projection of a shape in a given direction, like a spotlight casting a shadow
	*
	* @param Vector2 - the direction of the imaginary axis to project onto
	* @returns Range - the minimum projection and the maximum projection
	*/
	Range project(Vector2) override;

	/*
	* getPoints
	* overrides Collider's getPoints()
	*
	* calculates all of the points in the shape
	*
	* @returns std::vector<Vector2> - a list of points in the shape
	*/
	std::vector<Vector2> getPoints() override;

	/*
	* support
	* overrides Collider's support(Vector2 normal)
	*
	* calculates the points on a shape furtherest in a given direction
	*
	* @param Vector2 normal - the direction
	* @returns std::vector<Vector2> - a list of points that point the furthest in that direction
	*/
	std::vector<Vector2> support(Vector2 normal) override;

	/*
	* momentOfInertia
	* overrides Collider's momentOfInertia(float mass)
	*
	* calculates the "rotational mass" of the shape given it's mass
	*
	* @param float mass - the given weight of the object
	* @returns float - the rotational mass (formally called moment of inertia)
	*/
	float momentOfInertia(float mass) override;

	/*
	* generateHull
	* overrides Collider's generateHull()
	*
	* calculates the minimum AABB that contains the shape
	* @returns void
	*/
	void generateHull() override;

	/*
	* render
	* overrides Collider's render()
	*
	* renders the shape to the screen
	*
	* @param Application2D* app - the application to render the shape on
	* @returns void
	*/
	void render(Application2D* app) override;
};