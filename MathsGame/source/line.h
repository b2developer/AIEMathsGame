#pragma once
#include "collider.h"

/*
* class Line
* child class of Collider
*
* a line that can be tested for intersection with other shapes
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Line : public Collider
{
public:

	//the points that the line exists between
	Vector2 start = { 0,0 };
	Vector2 end = { 0,0 };

	/*
	* Line()
	* default constructor
	*/
	Line() { colliderType = BoundsType::LINE; };

	/*
	* Line(Vector2, Vector2)
	* constructor - immediately sets the start and end points of the Line
	*
	* @param Vector2 - the starting point
	* @param Vector2 - the ending point
	*/
	Line(Vector2, Vector2);

	/*
	* ~Line()
	* default constructor
	*/
	~Line() {};

	/*
	* getAxes
	* overrides Collider's getAxes()
	*
	* calculates the axis to test with a Line
	*
	* @param Collider& - the other shape in the collision test, this is necessary for circles
	* @returns std::vector<Vector2> - a list of directional vectors to test
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