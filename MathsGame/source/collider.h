#pragma once
#include <vector>
#include <limits>
#include "maths_library.h"
#include "transform.h"

//forward declaration
class AABB;
class Application2D;

//anything closer to another thing than this range is considered equal to the other thing
#define EPSILON 1e-5f

//defines the collider type
enum class BoundsType
{
	BASE,
	POINT,
	LINE,
	AABB,
	POLYGON,
	CIRCLE,
};

/*
* struct Range
* 
* describes a range numbers between a minimum and a maximum
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
struct Range
{
	float min = std::numeric_limits<float>::max();
	float max = -std::numeric_limits<float>::max();
};

/*
* class Collider
* abstract class
*
* represents a common type for shapes such as a Circle, AABB or Polygon
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Collider
{
public:

	Transform transform = Transform{}; //transformation of the collider
	BoundsType colliderType = BoundsType::BASE; //type id

	AABB* hull = nullptr; //aabb hull

	unsigned int layer = 0b11111; //collider bits, if tested against another collider they must both have a 1 at at least one position

	/*
	* Collider()
	* default constructor
	*/
	Collider() {};

	/*
	* ~Collider()
	* destructor - deletes the hull
	*/
	~Collider();

	/*
	* getAxes
	* abstract function
	*
	* calculates all of the axes needed to satsify testing collisions with Seperating Axis Theorem
	*
	* @param Collider& - the other shape in the collision test, this is necessary for circles
	* @returns std::vector<Vector2> - a list of directional vectors to test
	*/
	virtual std::vector<Vector2> getAxes(Collider&) = 0;

	/*
	* project
	* abstract function
	*
	* calculates the projection of a shape in a given direction, like a spotlight casting a shadow
	*
	* @param Vector2 - the direction of the imaginary axis to project onto
	* @returns Range - the minimum projection and the maximum projection
	*/
	virtual Range project(Vector2) = 0;

	/*
	* getPoints
	* abstract function
	*
	* calculates all of the points in the shape
	*
	* @returns std::vector<Vector2> - a list of points in the shape
	*/
	virtual std::vector<Vector2> getPoints() = 0;

	/*
	* support
	* abstract function
	*
	* calculates the points on a shape furtherest in a given direction
	*
	* @param Vector2 normal - the direction
	* @returns std::vector<Vector2> - a list of points that point the furthest in that direction
	*/
	virtual std::vector<Vector2> support(Vector2 normal) = 0;

	/*
	* momentOfInertia
	* abstract function
	*
	* calculates the "rotational mass" of the shape given it's mass
	*
	* @param float mass - the given weight of the object
	* @returns float - the rotational mass (formally called moment of inertia)
	*/
	virtual float momentOfInertia(float mass) = 0;

	/*
	* generateHull
	* abstract function
	*
	* calculates the minimum AABB that contains the shape
	* @returns void
	*/
	virtual void generateHull() = 0;

	/*
	* render
	* abstract function
	*
	* renders the shape to the screen
	*
	* @param Application2D* app - the application to render the shape on
	* @returns void
	*/
	virtual void render(Application2D* app) = 0;

	
};