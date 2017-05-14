#pragma once
#include "Vector2.h"
#include "dllmain.h"

/*
* Matrix2T
* template class
* 2x2 matrix structure
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Matrix2T
{
public:

	Vector2T<T> mat[2]; //rows of numbers

	/*
	* Matrix2T()
	* default constructor
	* fills matrix with zeroes
	*/
	MATHSLIBRARY_API Matrix2T();

	/*
	* Matrix2T()
	* argument constructor
	*
	* @param T - the 1st element of the 1st row
	* @param T - the 2nd element of the 1st row
	* @param T - the 1st element of the 2nd row
	* @param T - the 2nd element of the 2nd row
	*/
	MATHSLIBRARY_API Matrix2T(T m11, T m12, T m21, T m22);

	/*
	* Matrix2T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Matrix2T() {};

	/*
	* operator[]
	* subscript overload
	*
	* @param const int - the axis to access
	* @returns Vector2T& - the axis accessed
	*/
	MATHSLIBRARY_API Vector2T<T>& operator[](const int index);

	/*
	* operator T *
	* cast to T pointer overload
	*
	* @returns T * - the address of the first item in the matrix
	*/
	MATHSLIBRARY_API operator T *();

	/*
	* operator*
	* applys matrix multiplication to two Matrix2Ts
	*
	* @param Matrix2T - the other matrix to use
	* @returns Matrix2T - the product of the matrices
	*/
	MATHSLIBRARY_API Matrix2T<T> operator*(Matrix2T<T> other);

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
	* setRotate
	* generates a 2D rotation matrix given the amount of rotation in radians
	* https://en.wikipedia.org/wiki/Rotation_matrix
	*
	* @param T - the amount of radians the matrix will represent
	* @returns void
	*/
	MATHSLIBRARY_API void setRotate(T radians);

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
	*
	* @returns bool - indicating if the inversion worked or not
	*/
	MATHSLIBRARY_API bool invert();


};

using Matrix2 = Matrix2T<float>;