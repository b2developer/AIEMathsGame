#pragma once
#include <math.h>
#include "dllmain.h"

#define TEMPLATE template<typename T>

//forward decleration
TEMPLATE
class Matrix2T;

TEMPLATE
class Vector3T;

TEMPLATE
class Vector4T;

//which orientation to use when calculating the normal
enum class NormalDirection
{
	LEFT,
	RIGHT,
};

/*
* Vector2T
* template class
* 2D coordinate / offset structure
* 
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Vector2T
{
public:

	/*
	* Vector2T()
	* default constructor
	*/
	MATHSLIBRARY_API Vector2T() {};

	/*
	* Vector2T()
	* argument constructor
	*
	* @param T - the x coordinate
	* @param T - the y coordinate
	*/
	MATHSLIBRARY_API Vector2T(T _x, T _y) { x = _x; y = _y; };

	/*
	* Vector2T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Vector2T() {};

	/*
	* operator[]
	* subscript overload
	*
	* @param const int - the axis to access
	* @returns T& - the axis accessed
	*/
	MATHSLIBRARY_API T& operator[](const int index);

	/*
	* operator T *
	* cast to T pointer overload
	*
	* @returns T * - the address of the first item in the vector
	*/
	MATHSLIBRARY_API operator T*();

	/*
	* operator Vector3T<T>
	* cast to Vector3T<T> overload
	*
	* @returns Vector3T<T> - the Vector2 as a Vector3
	*/
	MATHSLIBRARY_API operator Vector3T<T>();

	/*
	* operator Vector4T<T>
	* cast to Vector4T<T> overload
	*
	* @returns Vector4T<T> - the Vector2 as a Vector4
	*/
	MATHSLIBRARY_API operator Vector4T<T>();

	/*
	* operator +
	* adds 2 vectors together
	*
	* @param const Vector2T - the other vector to use
	* @returns Vector2T - the sum
	*/
	MATHSLIBRARY_API Vector2T operator+(const Vector2T other);

	/*
	* operator +=
	* adds 2 vectors together
	*
	* @param const Vector2T - the other vector to use
	* @returns void
	*/
	MATHSLIBRARY_API void operator+=(const Vector2T other);

	/*
	* operator -
	* subtracts the other vector from the first
	*
	* @param const Vector2T - the other vector to use
	* @returns Vector2T - the resultant
	*/
	MATHSLIBRARY_API Vector2T operator-(const Vector2T other);

	/*
	* operator *
	* multiplies a vector by a scalar
	*
	* @param const T scalar - the number to multiply all components by
	* @returns Vector2T - the resultant
	*/
	MATHSLIBRARY_API Vector2T operator*(const T scalar);

	/*
	* operator /
	* divdes a vector by a scalar
	*
	* @param const T scalar - the number to divde all components by
	* @returns Vector2T - the resultant
	*
	*/
	MATHSLIBRARY_API Vector2T operator/(const T scalar);

	/*
	* dot
	* calculates the dot product of two vectors
	*
	* @param const Vector2T - the other vector to use
	* @returns T - the dot product
	*/
	MATHSLIBRARY_API T dot(const Vector2T other);

	/*
	* sqrMagnitude
	* calculates the squared length of a vector
	*
	* @returns T - the squared length of the vector
	*/
	MATHSLIBRARY_API T sqrMagnitude();

	/*
	* magnitude
	* calculates the length of a vector
	*
	* @returns T - the length of the vector
	*/
	MATHSLIBRARY_API T magnitude();

	/*
	* normalise
	* scales the vector so that it's magnitude is 1
	* a vector with a magnitude of 1 is called a unit 
	*
	* @returns void
	*/
	MATHSLIBRARY_API void normalise();

	/*
	* normalise
	* creates a normalised version of a vector without
	* normalising the vector object that called
	*
	* @returns Vector2T<T> - a normalised vector
	*/
	MATHSLIBRARY_API Vector2T<T> normalised();

	/*
	* operator *
	* multiplies a vector by a transformation matrix
	*
	* @param Matrix2 matrix - the matrix to transform the vector with
	* @returns Vector2T<T> - the resultant
	*/
	MATHSLIBRARY_API Vector2T<T> operator*(Matrix2T<T> matrix);

	/*
	* normal
	*
	* returns the left or normal vector
	*
	* @param NormalDirection direction - which normal to calculate (LEFT by default)
	* @returns Vector2T<T> - the normal vector
	*/
	MATHSLIBRARY_API Vector2T<T> normal(NormalDirection direction = NormalDirection::LEFT);

	/*
	* getRotation
	*
	* calculates the orientation of the vector
	*
	* @returns T - the rotation of the vector in radians
	*/
	MATHSLIBRARY_API T getRotation();

	#pragma region swizzling
	/*
	* GetXX
	*
	* swizzles vector to (x,x)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetXX();

	/*
	* GetYX
	*
	* swizzles vector to (y,x)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetYX();

	/*
	* GetYY
	*
	* swizzles vector to (y,y)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetYY();

	/*
	* GetXXX
	*
	* swizzles vector to (x,x,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXXX();

	/*
	* GetXXY
	*
	* swizzles vector to (x,x,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXXY();

	/*
	* GetXYX
	*
	* swizzles vector to (x,y,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXYX();

	/*
	* GetXYY
	*
	* swizzles vector to (x,y,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXYY();

	/*
	* GetYXX
	*
	* swizzles vector to (y,x,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYXX();

	/*
	* GetYXY
	*
	* swizzles vector to (y,x,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYXY();

	/*
	* GetYYX
	*
	* swizzles vector to (y,y,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYYX();

	/*
	* GetYYY
	*
	* swizzles vector to (y,y,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYYY();

	/*
	* GetXXXX
	*
	* swizzles vector to (x,x,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXXX();

	/*
	* GetXXXY
	*
	* swizzles vector to (x,x,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXXY();

	/*
	* GetXXYX
	*
	* swizzles vector to (x,x,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXYX();

	/*
	* GetXXYY
	*
	* swizzles vector to (x,x,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXYY();

	/*
	* GetXYXX
	*
	* swizzles vector to (x,y,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYXX();

	/*
	* GetXYXY
	*
	* swizzles vector to (x,y,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYXY();

	/*
	* GetXYYX
	*
	* swizzles vector to (x,y,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYYX();

	/*
	* GetXYYY
	*
	* swizzles vector to (x,y,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYYY();

	/*
	* GetYXXX
	*
	* swizzles vector to (y,x,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXXX();

	/*
	* GetYXXY
	*
	* swizzles vector to (y,x,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXXY();

	/*
	* GetYXYX
	*
	* swizzles vector to (y,x,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXYX();

	/*
	* GetYXYY
	*
	* swizzles vector to (y,x,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXYY();

	/*
	* GetYYXX
	*
	* swizzles vector to (y,y,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYXX();

	/*
	* GetYYXY
	*
	* swizzles vector to (y,y,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYXY();

	/*
	* GetYYYX
	*
	* swizzles vector to (y,y,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYYX();

	/*
	* GetYYYY
	*
	* swizzles vector to (y,y,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYYY();


	#pragma endregion

	T x = 0, y = 0;
};

using Vector2 = Vector2T<float>;

/*
* operator *
* template function
* multiplies a vector by a scalar
*
* @param const float scalar - the number to multiply all components by
* @param const Vector2T<T> vector - the vector to multiply
* @returns Vector2T<T> - the resultant
*/
TEMPLATE
Vector2T<T> operator*(const float scalar, const Vector2T<T> vector);

//multiplication operator (reordered)
TEMPLATE
Vector2T<T> operator*(const float scalar, const Vector2T<T> vector)
{
	return Vector2T<T>{ vector.x * scalar, vector.y * scalar };
}



/*
* operator /
* template function
* divdes a vector by a scalar
*
* @param const float scalar - the number to divde all components by
* @param const Vector2T<T> vector - the vector to divide
* @returns Vector2T<T> - the resultant
*/
TEMPLATE
Vector2T<T> operator/(const float scalar, const Vector2T<T> vector);

//division operator (reordered)
TEMPLATE
Vector2T<T> operator/(const float scalar, const Vector2T<T> vector)
{
	return Vector2T<T>{ scalar / vector.x, scalar / vector.y};
}



/*
* operator *
* template function
* multiplies a vector by a transformation matrix
*
* @param Matrix2T<T> matrix - the matrix to transform the vector with
* @param Vector2T<T> vector - the vector to copy and apply the transformation to
* @returns Vector2T<T> - the resultant
*/
TEMPLATE
Vector2T<T> operator*(Matrix2T<T> matrix, Vector2T<T> vector);

//matrix transformation (reordered)
TEMPLATE
Vector2T<T> operator*(Matrix2T<T> matrix, Vector2T<T> vector)
{
	Vector2T<T> product = {};

	//a = Vector2T<T> vector passed into the function
	//b = Matrix2 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 2; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 2; i++)
		{
			product[bn] = product[bn] + vector[i] * matrix.mat[i][bn];
		}
	}

	return product;
}
