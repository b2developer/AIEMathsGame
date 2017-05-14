#pragma once
#include "maths_library.h"
#include <vector>

#define PI 3.14159265359f

/*
* class Transform
*
* manages transformations in individual matrices, combines them when necessary
* stores the data required to generate a translation, rotation and scaling matrix
* also sets parents and children, updates them with the transform when necessary 
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Transform
{
public:

	Transform* parent = nullptr; //pointer to the parent
	std::vector<Transform*> children; //pointers to children

	Matrix3 localTransform = Matrix3{}; //transformation in local space
	Matrix3 globalTransform = Matrix3{}; //transformation in global space

	Vector2 translation = Vector2{0,0}; //translation as a vector
	float rotation = 0.0f; //rotation in radians
	Vector2 scale = Vector2{1,1}; //scale as a vector

	/*
	* Transform()
	* constructor, assigns default values
	*/
	Transform();

	/*
	* Transform()
	* constructor - assigns values through arguments
	*
	* @param Vector2 _translation
	* @param float _rotation
	* @param Vector2 _scale
	*/
	Transform(Vector2 _translation, float _rotation, Vector2 _scale) 
	{
		translation = _translation;
		rotation = _rotation;
		scale = _scale;
	}

	/*
	* Transform()
	* default destructor
	*/
	~Transform() {};

	/*
	* updateLocalTransform
	*
	* generates a transformation matrix from translation, rotation and scale
	*
	* @returns void
	*/
	void updateLocalTransform();

	/*
	* updateGlobalTransform
	*
	* generates a transformation matrix from translation, rotation and scale
	* adds the transforms from all parents recursively
	*
	* @returns void
	*/
	void updateGlobalTransform();

	/*
	* updateChildren
	*
	* recursively updates children with a the new transformation matrix
	*
	* @returns void
	*/
	void updateChildren();

	/*
	* setParent
	* 
	* sets the parent of the transform, inherits the transformation
	* of the parent and all of it's parents in the future
	* also adds a child pointer to the parent
	*
	* @param Transform* parentPtr - the transform to parent to
	* @returns void
	*/
	void setParent(Transform* parentPtr);

	/*
	* addChild
	*
	* adds a child to the transform, the child will inherit
	* the transformation of this transform in the future
	* also sets the child's parent to this transform
	*
	* @param Transform* child - the transform to add as a child
	* @returns void
	*/
	void addChild(Transform* child);

	/*
	* removeParent
	*
	* removes the transform's parent, updates the transform
	* to convert the final positions to coordinate space
	* does nothing if the transform does not have a parent
	* also removes the child pointer from the parent
	*
	* @param Transform* parent - the transform to parent to
	* @returns void
	*/
	void removeParent();

	/*
	* removeChild
	*
	* removes the transform's parent, updates the transform
	* to convert the final positions to coordinate space
	* does nothing if the transform does not have the child
	* also resets the parent of the child
	*
	* @param Transform* parent - the transform to parent to
	* @returns void
	*/
	void removeChild(Transform* child);
};

/*
* extractMatrix()
*
* pulls the individual translation, rotation and scale
* from a full transformation matrix
*
* @param Matrix3 matrix - the transformation matrix to extract from
* @returns Transform - the transform containing the individual transformations
*/
Transform extractMatrix(Matrix3 matrix);