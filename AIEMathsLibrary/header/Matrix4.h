#pragma once
#include "Vector4.h"
#include "dllmain.h"

/*
* Matrix4T
* template class
* 4x4 matrix structure
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Matrix4T
{
public:

	Vector4T<T> mat[4]; //rows of numbers

	/*
	* Matrix4T()
	* default constructor
	* fills matrix with zeroes
	*/
	MATHSLIBRARY_API Matrix4T();

	/*
	* Matrix4T()
	* argument constructor
	*
	* @param T - the 1st element of the 1st column
	* @param T - the 2nd element of the 1st column
	* @param T - the 3rd element of the 1st column
	* @param T - the 4th element of the 1st column
	*
	* @param T - the 1st element of the 2nd column
	* @param T - the 2nd element of the 2nd column
	* @param T - the 3rd element of the 2nd column
	* @param T - the 4th element of the 2nd column
	*
	* @param T - the 1st element of the 3rd column
	* @param T - the 2nd element of the 3rd column
	* @param T - the 3rd element of the 3rd column
	* @param T - the 4th element of the 3rd column
	*
	* @param T - the 1st element of the 4th column
	* @param T - the 2nd element of the 4th column
	* @param T - the 3rd element of the 4th column
	* @param T - the 4th element of the 4th column
	*/
	MATHSLIBRARY_API Matrix4T(T m11, T m12, T m13, T m14,
			T m21, T m22, T m23, T m24,
			T m31, T m32, T m33, T m34,
			T m41, T m42, T m43, T m44);
	/*
	* Matrix4T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Matrix4T() {};

	/*
	* operator[]
	* subscript overload
	*
	* @param const int - the axis to access
	* @returns Vector4T& - the axis accessed
	*/
	MATHSLIBRARY_API Vector4T<T>& operator[](const int index);

	/*
	* operator T *
	* cast to T pointer overload
	*
	* @returns T * - the address of the first item in the matrix
	*/
	MATHSLIBRARY_API operator T *();

	/*
	* operator*
	* applys matrix multiplication to two Matrix4Ts
	*
	* @param const Matrix4T - the other matrix to use
	* @returns Matrix4T - the product of the matrices
	*/
	MATHSLIBRARY_API Matrix4T<T> operator*(const Matrix4T<T> other);

	/*
	* identity
	* converts the matrix to an identity matrix
	* 1 0 0...
	* 0 1 0...
	* 0 0 1...
	* . . .
	* . . .
	*
	* @returns void
	*/
	MATHSLIBRARY_API void identity();

	/*
	* setRotateX
	* generates a 3D homogeneous rotation matrix around the X axis given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotateX(T radians);

	/*
	* setRotateY
	* generates a 3D homogeneous rotation matrix around the Y axis given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotateY(T radians);

	/*
	* setRotateZ
	* generates a 3D homogeneous rotation matrix around the Z axis given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotateZ(T radians);

	/*
	* transpose
	* swaps the row and column positions of each element around
	*
	* a b  becomes --->  a c
	* c d				 b d
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void transpose();

	/*
	* determinant
	* calcualates the determinant of the matrix
	*
	* this process is massive for a 4x4 matrix, so
	* the calculation is broken down into 4 3x3 matrix determinants
	*
	* @returns T - the determinant of the matrix
	*/
	MATHSLIBRARY_API T determinant();

	/*
	* invert
	* inverts the matrix
	* sometimes matrices aren't invertible
	* http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	*
	* @returns bool - indicating if the inversion worked or not
	*/
	MATHSLIBRARY_API bool invert();

	/*
	* setScale
	*
	* generates a scaling matrix
	*
	* @param Vector3T<T> scale - the new scale of the matrix
	* @returns void
	*/
	MATHSLIBRARY_API void setScale(Vector3T<T> scale);

	/*
	* setTranslate
	*
	* generates a translation matrix
	*
	* @param Vector3T<T> translate - the new translation of the matrix
	* @returns void
	*/
	MATHSLIBRARY_API void setTranslate(Vector3T<T> translate);

	/*
	* translate
	*
	* adds a translation to a matrix
	*
	* @param Vector3T<T> translate - the translation to add
	* @returns void
	*/
	MATHSLIBRARY_API void translate(Vector3T<T> translate);

	/*
	* scale
	*
	* scales a matrix
	*
	* @param Vector3T<T> scale - the scale to apply
	* @returns void
	*/
	MATHSLIBRARY_API void scale(Vector3T<T> scale);

	/*
	* getScale
	*
	* gets the scale of a 3D transformation matrix (a 4D matrix)
	*
	* @returns Vector3T<T> - the scale along each axis
	*/
	MATHSLIBRARY_API Vector3T<T> getScale();

	/*
	* rotateX
	*
	* applies a rotation to a 3D transformation matrix
	* along the x axis (yz affected)
	*
	* @param T radians - the amount of rotation to apply
	* @returns void
	*/
	MATHSLIBRARY_API void rotateX(T radians);

	/*
	* rotateY
	*
	* applies a rotation to a 3D transformation matrix
	* along the y axis (xz affected)
	*
	* @param T radians - the amount of rotation to apply
	* @returns void
	*/
	MATHSLIBRARY_API void rotateY(T radians);

	/*
	* rotateZ
	*
	* applies a rotation to a 3D transformation matrix
	* along the z axis (xy affected)
	*
	* @param T radians - the amount of rotation to apply
	* @returns void
	*/
	MATHSLIBRARY_API void rotateZ(T radians);

	/*
	* rotateEuler
	*
	* applies 3 rotations in a specific order
	* Z then Y then X
	*
	* @param Vector3T<T> angles - the angles to rotate by
	* @returns void
	*/
	MATHSLIBRARY_API void rotateEuler(Vector3T<T> angles);

	/*
	* getRotationX
	*
	* gets the rotation around the X axis of a 3D transformation matrix (a 4D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationX();

	/*
	* getRotationY
	*
	* gets the rotation around the Y axis of a 3D transformation matrix (a 4D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationY();

	/*
	* getRotationZ
	*
	* gets the rotation around the Z axis of a 3D transformation matrix (a 4D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationZ();

	/*
	* getEuler
	*
	* gets the rotation along all axes as euler angles
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns Vector3T<T> - the rotation in radians
	*/
	MATHSLIBRARY_API Vector3T<T> getEuler();

	/*
	* lookAt
	*
	* generates a rotation matrix which will orient
	* an observer positioned at eye to face towards 
	* target. the up vector is used to make sure that
	* the orientation is sensible (not upside-down)
	*
	* @param Vector3T<T> eye - the position of the observer
	* @param Vector3T<T> target - the position to orient towards
	* @param Vector3T<T> up - the global up vector
	*/
	MATHSLIBRARY_API void lookAt(Vector3T<T> eye, Vector3T<T> target, Vector3T<T> up);

	/*
	* generateProjection
	*
	* creates a matrix that will transform a point as if
	* an observer was looking at it with a camera
	* http://www.codinglabs.net/article_world_view_projection_matrix.aspx
	*
	* @param T fovX - field of view along the x axis (must be less than PI)
	* @param T fovY - field of view along the y axis (must be less than PI)
	* @param T zNear - the near clipping plane, anything closer will be clamped
	* @param T zFar - the far clipping plane, anything further will be clamped
	* @returns void
	*/
	MATHSLIBRARY_API void generateProjection(T fovX, T fovY, T zNear, T zFar);

};

using Matrix4 = Matrix4T<float>;