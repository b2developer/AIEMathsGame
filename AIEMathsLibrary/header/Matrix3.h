#pragma once
#include "Vector3.h"
#include "dllmain.h"

/*
* Matrix3T
* template class
* 3x3 matrix structure
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Matrix3T
{
public:

	Vector3T<T> mat[3]; //rows of numbers

	/*
	* Matrix3T()
	* default constructor
	* fills matrix with zeroes
	*/
	MATHSLIBRARY_API Matrix3T();

	/*
	* Matrix3T()
	* argument constructor
	*
	* @param T - the 1st element of the 1st column
	* @param T - the 2nd element of the 1st column
	* @param T - the 3rd element of the 1st column
	*
	* @param T - the 1st element of the 2nd column
	* @param T - the 2nd element of the 2nd column
	* @param T - the 3rd element of the 2nd column
	*
	* @param T - the 1st element of the 3rd column
	* @param T - the 2nd element of the 3rd column
	* @param T - the 3rd element of the 3rd column
	*/
	MATHSLIBRARY_API  Matrix3T(T m11, T m12, T m13,
		    T m21, T m22, T m23,
			T m31, T m32, T m33);

	/*
	* Matrix3T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Matrix3T() {};

	/*
	* operator[]
	* subscript overload
	*
	* @param const int - the axis to access
	* @returns Vector3T& - the axis accessed
	*/
	MATHSLIBRARY_API Vector3T<T>& operator[](const int index);

	/*
	* operator T *
	* cast to T pointer overload
	*
	* @returns T * - the address of the first item in the matrix
	*/
	MATHSLIBRARY_API operator T *();

	/*
	* operator*
	* applys matrix multiplication to two Matrix3Ts
	*
	* @param const Matrix3T - the other matrix to use
	* @returns Matrix3T - the product of the matrices
	*/
	MATHSLIBRARY_API Matrix3T<T> operator*(const Matrix3T<T> other);

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
	* generates a 3D rotation matrix around the X axis given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotateX(T radians);

	/*
	* setRotateY
	* generates a 3D rotation matrix around the Y axis given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotateY(T radians);

	/*
	* setRotateZ
	* generates a 3D rotation matrix around the Z axis given the amount of rotation in radians
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
	* @param Vector2T<T> scale - the new scale of the matrix
	* @returns void
	*/
	MATHSLIBRARY_API void setScale(Vector2T<T> scale);

	/*
	* setTranslate
	*
	* generates a translation matrix
	*
	* @param Vector2T<T> translate - the new translation of the matrix
	* @returns void
	*/
	MATHSLIBRARY_API void setTranslate(Vector2T<T> translate);

	/*
	* translate
	*
	* adds a translation to a matrix
	*
	* @param Vector2T<T> translate - the translation to add
	* @returns void
	*/
	MATHSLIBRARY_API void translate(Vector2T<T> translate);

	/*
	* scale
	*
	* scales a matrix
	*
	* @param Vector2T<T> scale - the scale to apply
	* @returns void
	*/
	MATHSLIBRARY_API void scale(Vector2T<T> scale);

	/*
	* getScale
	*
	* gets the scale of a 2D transformation matrix (a 3D matrix)
	*
	* @returns Vector2T<T> - the scale along each axis
	*/
	MATHSLIBRARY_API Vector2T<T> getScale();

	/*
	* getRotation
	*
	* gets the rotation of a 2D transformation matrix (a 3D matrix)
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotation();

	/*
	* rotateX
	*
	* applies a rotation to a 3D rotation matrix
	* along the x axis (yz affected)
	*
	* @param T radians - the amount of rotation to apply
	* @returns void
	*/
	MATHSLIBRARY_API void rotateX(T radians);

	/*
	* rotateY
	*
	* applies a rotation to a 3D rotation matrix
	* along the y axis (xz affected)
	*
	* @param T radians - the amount of rotation to apply
	* @returns void
	*/
	MATHSLIBRARY_API void rotateY(T radians);

	/*
	* rotateZ
	*
	* applies a rotation to a 3D rotation matrix
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
	* gets the rotation around the X axis of a 3D rotation matrix (a 3D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationX();

	/*
	* getRotationY
	*
	* gets the rotation around the Y axis of a 3D rotation matrix (a 3D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationY();

	/*
	* getRotationZ
	*
	* gets the rotation around the Z axis of a 3D rotation matrix (a 3D matrix)
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns T - the rotation in radians
	*/
	MATHSLIBRARY_API T getRotationZ();

	/*
	* getEuler
	*
	* gets the rotation along all axes as euler angles from a 3D rotation matrix
	* https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
	*
	* @returns Vector3T<T> - the rotation in radians
	*/
	MATHSLIBRARY_API Vector3T<T> getEuler();

	/*
	* lookAt
	*
	* generates a rotation matrix which transforms
	* a forwards vector into the given direction
	*
	* @param Vector3T<T> direction - the direction to generate a rotation matrix from
	* @param Vector3T<T> up - the global up vector
	* @returns void
	*/
	MATHSLIBRARY_API void lookAt(Vector3T<T> direction, Vector3T<T> up);
};

using Matrix3 = Matrix3T<float>;