#pragma once
#include "collider.h"

/*
* class Polygon
* child class of Collider
*
* a shape, stored as a set of points. sides are made by connecting one point 
* to the next point in the array. the last side is formed by connecting the last point to the first
* 
* WARNING: the order is crucial, if the points are passed in the wrong order, funky things will happen
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Polygon : public Collider
{
public:

	//the polygon's point list
	std::vector<Vector2> points;

	/*
	* Polygon()
	* default constructor
	*/
	Polygon() { colliderType = BoundsType::POLYGON; };

	/*
	* Polygon(Vector2, Vector2)
	* constructor - immediately sets the Polygon's position
	*
	* @param std::vector<Vector2> - the list of ordered points
	*/
	Polygon(std::vector<Vector2>);

	/*
	* ~Polygon()
	* default constructor
	*/
	~Polygon() {};

	/*
	* getAxes
	* overrides Collider's getAxes()
	*
	* calculates all axes to test with a Polygon
	*
	* @param Collider& - the other shape in the collision test, this is necessary for circles
	* @returns std::vector<Vector2> - returns a list of all the sides the points of the polygon form
	*/
	std::vector<Vector2> getAxes(Collider&) override;

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