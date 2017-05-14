#include "transform.h"

Transform::Transform()
{
	translation = Vector2{ 0,0 };
	rotation = 0.0f;
	scale = Vector2{ 1,1 };

	updateGlobalTransform();
}

//creates a local transformation matrix out of translation, rotation and scale
void Transform::updateLocalTransform()
{
	Matrix3 translationMatrix;
	translationMatrix.setTranslate(translation);

	Matrix3 rotationMatrix;
	rotationMatrix.setRotateZ(rotation);

	Matrix3 scaleMatrix;
	scaleMatrix.setScale(scale);

	//scale * rotation * translation (the desired order)
	localTransform = translationMatrix * rotationMatrix * scaleMatrix;
}

//creates a global transformation matrix out of position, rotation and scale recursively from all parents
void Transform::updateGlobalTransform()
{
	Matrix3 translationMatrix;
	translationMatrix.setTranslate(translation);

	Matrix3 rotationMatrix;
	rotationMatrix.setRotateZ(rotation);

	Matrix3 scaleMatrix;
	scaleMatrix.setScale(scale);

	//if the transform has a parent
	if (parent == nullptr)
	{
		//scale * rotation * translation (the desired order)
		globalTransform = translationMatrix * rotationMatrix * scaleMatrix;
	}
	else
	{
		parent->updateGlobalTransform();

		//scale * rotation * translation * parent.... (the desired order)
		globalTransform = parent->globalTransform * translationMatrix * rotationMatrix * scaleMatrix;
	}

	updateLocalTransform();
}

//updates all children's global transformation matrices recursively
void Transform::updateChildren()
{
	size_t childrenSize = children.size();

	//iterate through all of the children transforms
	for (size_t i = 0; i < childrenSize; i++)
	{
		Transform* child = children[i];

		Matrix3 translationMatrix;
		translationMatrix.setTranslate(child->translation);

		Matrix3 rotationMatrix;
		rotationMatrix.setRotateZ(child->rotation);

		Matrix3 scaleMatrix;
		scaleMatrix.setScale(child->scale);

		//this transform * child's local transform
		child->globalTransform = globalTransform * translationMatrix * rotationMatrix * scaleMatrix;

		//recursively apply the change to all transforms
		child->updateChildren();
	}
}

//sets the parent of the transform, adds the child to the parent
void Transform::setParent(Transform * parentPtr)
{
	//remove the parent properly first if the transform already has one
	if (parent != nullptr)
	{
		removeParent();
	}

	//get the global matrix
	updateGlobalTransform();

	parent = parentPtr;
	
	//invert the global matrix from the parent so that this transform doesn't change
	Matrix3 inv = parent->globalTransform;
	inv.invert();

	inv = inv * globalTransform;

	Transform overwrite = extractMatrix(inv);

	translation = overwrite.translation;
	rotation = overwrite.rotation;
	scale = overwrite.scale;

	scale = Vector2{ abs(scale.x), abs(scale.y) };

	//the parent got assigned over, reassign it
	parent = parentPtr;

	//add the child to the parent
	//----------------------------------------
	parent->children.push_back(this);
	//----------------------------------------
}

//adds the given transform pointer as a child
void Transform::addChild(Transform * child)
{
	children.push_back(child);

	//set the parent of the child to this transform
	//----------------------------------------
	//get the global matrix
	child->updateGlobalTransform();

	//invert the global matrix from the parent so that this transform doesn't change
	Matrix3 inv = globalTransform;
	inv.invert();

	inv = inv * child->globalTransform;

	Transform overwrite = extractMatrix(inv);

	child->translation = overwrite.translation;
	child->rotation = overwrite.rotation;
	child->scale = overwrite.scale;

	child->scale = Vector2{ abs(child->scale.x), abs(child->scale.y) };

	//the parent got assigned over, reassign it
	child->parent = this;
	//----------------------------------------
}

//sets the parent to null
void Transform::removeParent()
{
	//get the global matrix
	updateGlobalTransform();

	//set the transform's parameters to this
	Transform overwrite = extractMatrix(globalTransform);

	translation = overwrite.translation;
	rotation = overwrite.rotation;
	scale = overwrite.scale;

	scale = Vector2{ abs(scale.x), abs(scale.y) };
	
	//remove the child pointer from the parent
	//----------------------------------------
	size_t childSize = parent->children.size();

	//search for the child in children and erase it if found
	for (size_t i = 0; i < childSize; i++)
	{
		if (this == parent->children[i])
		{
			parent->children.erase(parent->children.begin() + i);
			break;
		}
	}
	//----------------------------------------

	parent = nullptr;
}

//removes the child transform (if it exists)
void Transform::removeChild(Transform * child)
{
	size_t childSize = children.size();

	//search for the child in children and erase it if found
	for (size_t i = 0; i < childSize; i++)
	{
		if (child == children[i])
		{
			children.erase(children.begin() + i);
			break;
		}
	}

	//reset the parent pointer from the child
	//----------------------------------------
	//get the global matrix
	//set the transform's parameters to this
	Transform overwrite = extractMatrix(child->globalTransform);

	child->translation = overwrite.translation;
	child->rotation = overwrite.rotation;
	child->scale = overwrite.scale;

	child->scale = Vector2{ abs(child->scale.x), abs(child->scale.y) };

	child->parent = nullptr;
	//----------------------------------------
}


//extracts individual translation, rotation and scale from one matrix
Transform extractMatrix(Matrix3 matrix)
{
	Transform transform = Transform{};

	//extract the transformed translation from the bottom row, this is not correct yet
	transform.translation = Vector2{ matrix[2][0], matrix[2][1] };

	//extract the scale
	transform.scale = matrix.getScale();

	//extract the rotation
	transform.rotation = matrix.getRotation();

	return transform;
}
