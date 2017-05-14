#pragma once
#include <math.h>
#include "dllmain.h"

#define TEMPLATE template<typename T>

//forward decleration
TEMPLATE
class Matrix3T;

TEMPLATE
class Vector2T;

TEMPLATE
class Vector4T;

/*
* Vector3T
* template class
* 3D coordinate / offset structure
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Vector3T
{
public:

	/*
	* Vector3T()
	* default constructor
	*/
	MATHSLIBRARY_API Vector3T() {};

	/*
	* Vector3T()
	* argument constructor
	*
	* @param T - the x coordinate
	* @param T - the y coordinate
	* @param T - the z coordinate
	*/
	MATHSLIBRARY_API Vector3T(T _x, T _y, T _z) { x = _x; y = _y; z = _z; };

	/*
	* Vector3T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Vector3T() {};

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
	MATHSLIBRARY_API operator T *();

	/*
	* operator Vector2T<T>
	* cast to Vector2T<T> overload
	*
	* @returns Vector2T<T> - the Vector3 as a Vector2
	*/
	MATHSLIBRARY_API operator Vector2T<T>();

	/*
	* operator Vector4T<T>
	* cast to Vector4T<T> overload
	*
	* @returns Vector4T<T> - the Vector3 as a Vector4
	*/
	MATHSLIBRARY_API operator Vector4T<T>();

	/*
	* operator +
	* adds 2 vectors together
	*
	* @param const Vector3T - the other vector to use
	* @returns Vector3T - the sum
	*/
	MATHSLIBRARY_API Vector3T operator+(const Vector3T other);

	/*
	* operator +=
	* adds 2 vectors together
	*
	* @param const Vector3T - the other vector to use
	* @returns void
	*/
	MATHSLIBRARY_API void operator+=(const Vector3T other);

	/*
	* operator -
	* subtracts the other vector from the first
	*
	* @param const Vector3T - the other vector to use
	* @returns Vector3T - the resultant
	*/
	MATHSLIBRARY_API Vector3T operator-(const Vector3T other);

	/*
	* operator *
	* multiplies a vector by a scalar
	*
	* @param const T scalar - the number to multiply all components by
	* @returns Vector3T - the resultant
	*/
	MATHSLIBRARY_API Vector3T operator*(const T scalar);

	/*
	* operator /
	* divdes a vector by a scalar
	*
	* @param const T scalar - the number to divde all components by
	* @returns Vector3T - the resultant
	*
	*/
	MATHSLIBRARY_API Vector3T operator/(const T scalar);

	/*
	* dot
	* calculates the dot product of two vectors
	*
	* @param const Vector3T - the other vector to use
	* @returns T - the dot product
	*/
	MATHSLIBRARY_API T dot(const Vector3T other);

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
	* @returns Vector3T - a normalised vector
	*/
	MATHSLIBRARY_API Vector3T normalised();

	/*
	* cross
	* computes a vector perpendicular to the two 
	* vectors given
	*
	* @param const Vector3T - the other vector to use
	* @returns Vector3T - the perpendicular vector
	*/
	MATHSLIBRARY_API Vector3T cross(const Vector3T<T> other);

	/*
	* operator *
	* multiplies a vector by a transformation matrix
	*
	* @param const Matrix3T matrix - the matrix to transform the vector with
	* @returns Vector3T - the resultant
	*/
	MATHSLIBRARY_API Vector3T operator*(const Matrix3T<T> matrix);

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
	* GetXY
	*
	* swizzles vector to (x,y)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetXY();

	/*
	* GetXZ
	*
	* swizzles vector to (x,z)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetXZ();

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
	* GetYZ
	*
	* swizzles vector to (y,z)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetYZ();

	/*
	* GetZX
	*
	* swizzles vector to (z,x)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetZX();

	/*
	* GetZY
	*
	* swizzles vector to (z,y)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetZY();

	/*
	* GetZZ
	*
	* swizzles vector to (z,z)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetZZ();

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
	* GetXXZ
	*
	* swizzles vector to (x,x,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXXZ();

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
	* GetXZX
	*
	* swizzles vector to (x,z,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXZX();

	/*
	* GetXZY
	*
	* swizzles vector to (x,z,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXZY();

	/*
	* GetXZZ
	*
	* swizzles vector to (x,z,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXZZ();

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
	* GetYXZ
	*
	* swizzles vector to (y,x,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYXZ();

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
	* GetYYZ
	*
	* swizzles vector to (y,y,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYYZ();

	/*
	* GetYZX
	*
	* swizzles vector to (y,z,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYZX();

	/*
	* GetYZY
	*
	* swizzles vector to (y,z,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYZY();

	/*
	* GetYZZ
	*
	* swizzles vector to (y,z,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYZZ();

	/*
	* GetZXX
	*
	* swizzles vector to (z,x,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZXX();

	/*
	* GetZXY
	*
	* swizzles vector to (z,x,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZXY();

	/*
	* GetZXZ
	*
	* swizzles vector to (z,x,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZXZ();

	/*
	* GetZYX
	*
	* swizzles vector to (z,y,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZYX();

	/*
	* GetZYY
	*
	* swizzles vector to (z,y,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZYY();

	/*
	* GetZYZ
	*
	* swizzles vector to (z,y,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZYZ();

	/*
	* GetZZX
	*
	* swizzles vector to (z,z,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZZX();

	/*
	* GetZZY
	*
	* swizzles vector to (z,z,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZZY();

	/*
	* GetZZZ
	*
	* swizzles vector to (z,z,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZZZ();

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
	* GetXXXZ
	*
	* swizzles vector to (x,x,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXXZ();

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
	* GetXXYZ
	*
	* swizzles vector to (x,x,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXYZ();

	/*
	* GetXXZX
	*
	* swizzles vector to (x,x,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXZX();

	/*
	* GetXXZY
	*
	* swizzles vector to (x,x,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXZY();

	/*
	* GetXXZZ
	*
	* swizzles vector to (x,x,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXZZ();

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
	* GetXYXZ
	*
	* swizzles vector to (x,y,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYXZ();

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
	* GetXYYZ
	*
	* swizzles vector to (x,y,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYYZ();

	/*
	* GetXYZX
	*
	* swizzles vector to (x,y,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYZX();

	/*
	* GetXYZY
	*
	* swizzles vector to (x,y,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYZY();

	/*
	* GetXYZZ
	*
	* swizzles vector to (x,y,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYZZ();

	/*
	* GetXZXX
	*
	* swizzles vector to (x,z,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZXX();

	/*
	* GetXZXY
	*
	* swizzles vector to (x,z,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZXY();

	/*
	* GetXZXZ
	*
	* swizzles vector to (x,z,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZXZ();

	/*
	* GetXZYX
	*
	* swizzles vector to (x,z,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZYX();

	/*
	* GetXZYY
	*
	* swizzles vector to (x,z,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZYY();

	/*
	* GetXZYZ
	*
	* swizzles vector to (x,z,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZYZ();

	/*
	* GetXZZX
	*
	* swizzles vector to (x,z,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZZX();

	/*
	* GetXZZY
	*
	* swizzles vector to (x,z,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZZY();

	/*
	* GetXZZZ
	*
	* swizzles vector to (x,z,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZZZ();

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
	* GetYXXZ
	*
	* swizzles vector to (y,x,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXXZ();

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
	* GetYXYZ
	*
	* swizzles vector to (y,x,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXYZ();

	/*
	* GetYXZX
	*
	* swizzles vector to (y,x,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXZX();

	/*
	* GetYXZY
	*
	* swizzles vector to (y,x,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXZY();

	/*
	* GetYXZZ
	*
	* swizzles vector to (y,x,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXZZ();

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
	* GetYYXZ
	*
	* swizzles vector to (y,y,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYXZ();

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

	/*
	* GetYYYZ
	*
	* swizzles vector to (y,y,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYYZ();

	/*
	* GetYYZX
	*
	* swizzles vector to (y,y,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYZX();

	/*
	* GetYYZY
	*
	* swizzles vector to (y,y,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYZY();

	/*
	* GetYYZZ
	*
	* swizzles vector to (y,y,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYZZ();

	/*
	* GetYZXX
	*
	* swizzles vector to (y,z,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZXX();

	/*
	* GetYZXY
	*
	* swizzles vector to (y,z,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZXY();

	/*
	* GetYZXZ
	*
	* swizzles vector to (y,z,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZXZ();

	/*
	* GetYZYX
	*
	* swizzles vector to (y,z,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZYX();

	/*
	* GetYZYY
	*
	* swizzles vector to (y,z,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZYY();

	/*
	* GetYZYZ
	*
	* swizzles vector to (y,z,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZYZ();

	/*
	* GetYZZX
	*
	* swizzles vector to (y,z,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZZX();

	/*
	* GetYZZY
	*
	* swizzles vector to (y,z,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZZY();

	/*
	* GetYZZZ
	*
	* swizzles vector to (y,z,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZZZ();

	/*
	* GetZXXX
	*
	* swizzles vector to (z,x,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXXX();

	/*
	* GetZXXY
	*
	* swizzles vector to (z,x,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXXY();

	/*
	* GetZXXZ
	*
	* swizzles vector to (z,x,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXXZ();

	/*
	* GetZXYX
	*
	* swizzles vector to (z,x,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXYX();

	/*
	* GetZXYY
	*
	* swizzles vector to (z,x,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXYY();

	/*
	* GetZXYZ
	*
	* swizzles vector to (z,x,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXYZ();

	/*
	* GetZXZX
	*
	* swizzles vector to (z,x,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXZX();

	/*
	* GetZXZY
	*
	* swizzles vector to (z,x,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXZY();

	/*
	* GetZXZZ
	*
	* swizzles vector to (z,x,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXZZ();

	/*
	* GetZYXX
	*
	* swizzles vector to (z,y,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYXX();

	/*
	* GetZYXY
	*
	* swizzles vector to (z,y,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYXY();

	/*
	* GetZYXZ
	*
	* swizzles vector to (z,y,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYXZ();

	/*
	* GetZYYX
	*
	* swizzles vector to (z,y,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYYX();

	/*
	* GetZYYY
	*
	* swizzles vector to (z,y,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYYY();

	/*
	* GetZYYZ
	*
	* swizzles vector to (z,y,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYYZ();

	/*
	* GetZYZX
	*
	* swizzles vector to (z,y,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYZX();

	/*
	* GetZYZY
	*
	* swizzles vector to (z,y,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYZY();

	/*
	* GetZYZZ
	*
	* swizzles vector to (z,y,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYZZ();

	/*
	* GetZZXX
	*
	* swizzles vector to (z,z,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZXX();

	/*
	* GetZZXY
	*
	* swizzles vector to (z,z,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZXY();

	/*
	* GetZZXZ
	*
	* swizzles vector to (z,z,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZXZ();

	/*
	* GetZZYX
	*
	* swizzles vector to (z,z,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZYX();

	/*
	* GetZZYY
	*
	* swizzles vector to (z,z,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZYY();

	/*
	* GetZZYZ
	*
	* swizzles vector to (z,z,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZYZ();

	/*
	* GetZZZX
	*
	* swizzles vector to (z,z,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZZX();

	/*
	* GetZZZY
	*
	* swizzles vector to (z,z,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZZY();

	/*
	* GetZZZZ
	*
	* swizzles vector to (z,z,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZZZ();


	#pragma endregion

	T x = 0, y = 0, z = 0;
};

using Vector3 = Vector3T<float>;

/*
* operator *
* template function
* multiplies a vector by a scalar
*
* @param const float scalar - the number to multiply all components by
* @param const Vector3T<T> vector - the vector to multiply
* @returns Vector3T<T> - the resultant
*/
TEMPLATE
Vector3T<T> operator*(const float scalar, const Vector3T<T> vector);

//multiplication operator (reordered)
TEMPLATE
Vector3T<T> operator*(const float scalar, const Vector3T<T> vector)
{
	return Vector3T<T>{ vector.x * scalar, vector.y * scalar, vector.z * scalar};
}



/*
* operator /
* template function
* divdes a vector by a scalar
*
* @param const float scalar - the number to divde all components by
* @param const Vector3T<T> vector - the vector to divide
* @returns Vector3T<T> - the resultant
*/
TEMPLATE
Vector3T<T> operator/(const float scalar, const Vector3T<T> vector);

//division operator (reordered)
TEMPLATE
Vector3T<T> operator/(const float scalar, const Vector3T<T> vector)
{
	return Vector3T<T>{ scalar / vector.x, scalar / vector.y, scalar / vector.z};
}




/*
* operator *
* template function
* multiplies a vector by a transformation matrix
*
* @param Matrix3T<T> matrix - the matrix to transform the vector with
* @param Vector3T<T> vector - the vector to copy and apply the transformation to
* @returns Vector3T<T> - the resultant
*/
TEMPLATE
Vector3T<T> operator*(Matrix3T<T> matrix, Vector3T<T> vector);

//matrix transformation (reordered)
TEMPLATE
Vector3T<T> operator*(Matrix3T<T> matrix, Vector3T<T> vector)
{
	Vector3T<T> product = {};

	//a = Vector3T<T> vector passed into the function
	//b = Matrix3 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 3; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 3; i++)
		{
			product[bn] = product[bn] + vector[i] * matrix.mat[i][bn];
		}
	}

	return product;
}
