#pragma once
#include <math.h>
#include "dllmain.h"

#define TEMPLATE template<typename T>

//forward decleration
TEMPLATE
class Matrix4T;

TEMPLATE
class Vector2T;

TEMPLATE
class Vector3T;

/*
* Vector4T
* homogenous 3D coordinate / offset structure
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE
class Vector4T
{
public:

	T x = 0, y = 0, z = 0, w = 0;

	/*
	* Vector4T()
	* default constructor
	*/
	MATHSLIBRARY_API Vector4T() {};

	/*
	* Vector4T()
	* argument constructor
	*
	* @param T - the x coordinate
	* @param T - the y coordinate
	* @param T - the z coordinate
	* @param T - the w coordinate
	*/
	MATHSLIBRARY_API Vector4T(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; };

	/*
	* Vector4T()
	* default destructor
	*/
	MATHSLIBRARY_API ~Vector4T() {};

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
	* operator Vector2T<T>
	* cast to Vector2T<T> overload
	*
	* @returns Vector2T<T> - the Vector4 as a Vector2
	*/
	MATHSLIBRARY_API operator Vector2T<T>();

	/*
	* operator Vector3T<T>
	* cast to Vector3T<T> overload
	*
	* @returns Vector3T<T> - the Vector4 as a Vector3
	*/
	MATHSLIBRARY_API operator Vector3T<T>();

	/*
	* operator +
	* adds 2 vectors together
	*
	* @param const Vector4T - the other vector to use
	* @returns Vector4T - the sum
	*/
	MATHSLIBRARY_API Vector4T operator+(const Vector4T other);

	/*
	* operator +=
	* adds 2 vectors together
	*
	* @param const Vector4T - the other vector to use
	* @returns void
	*/
	MATHSLIBRARY_API void operator+=(const Vector4T other);

	/*
	* operator -
	* subtracts the other vector from the first
	*
	* @param const Vector4T - the other vector to use
	* @returns Vector4T - the resultant
	*/
	MATHSLIBRARY_API Vector4T operator-(const Vector4T other);

	/*
	* operator *
	* multiplies a vector by a scalar
	*
	* @param const T scalar - the number to multiply all components by
	* @returns Vector4T - the resultant
	*/
	MATHSLIBRARY_API Vector4T operator*(const T scalar);

	/*
	* operator /
	* divdes a vector by a scalar
	*
	* @param const T scalar - the number to divde all components by
	* @returns Vector4T - the resultant
	*
	*/
	MATHSLIBRARY_API Vector4T operator/(const T scalar);

	/*
	* dot
	* calculates the dot product of two vectors
	*
	* @param const Vector4T - the other vector to use
	* @returns T - the dot product
	*/
	MATHSLIBRARY_API T dot(const Vector4T other);

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
	* @returns Vector4T - a normalised vector
	*/
	MATHSLIBRARY_API Vector4T normalised();

	/*
	* cross
	* computes a vector perpendicular to the two
	* vectors given.
	* 
	* implements cross as if the vector4 is a vector3
	* and zeroes the w axis
	*
	* @param const Vector4T - the other vector to use
	* @returns Vector4T - the perpendicular vector
	*/
	MATHSLIBRARY_API Vector4T cross(const Vector4T other);

	/*
	* operator *
	* multiplies a vector by a transformation matrix
	*
	* @param const Matrix4T matrix - the matrix to transform the vector with
	* @returns Vector4T - the resultant
	*/
	MATHSLIBRARY_API Vector4T operator*(const Matrix4T<T> matrix);

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
	* GetXW
	*
	* swizzles vector to (x,w)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetXW();

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
	* GetYW
	*
	* swizzles vector to (y,w)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetYW();

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
	* GetZW
	*
	* swizzles vector to (z,w)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetZW();

	/*
	* GetWX
	*
	* swizzles vector to (w,x)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetWX();

	/*
	* GetWY
	*
	* swizzles vector to (w,y)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetWY();

	/*
	* GetWZ
	*
	* swizzles vector to (w,z)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetWZ();

	/*
	* GetWW
	*
	* swizzles vector to (w,w)
	*
	* @returns Vector2T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector2T<T> GetWW();

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
	* GetXXW
	*
	* swizzles vector to (x,x,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXXW();

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
	* GetXYZ
	*
	* swizzles vector to (x,y,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXYZ();

	/*
	* GetXYW
	*
	* swizzles vector to (x,y,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXYW();

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
	* GetXZW
	*
	* swizzles vector to (x,z,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXZW();

	/*
	* GetXWX
	*
	* swizzles vector to (x,w,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXWX();

	/*
	* GetXWY
	*
	* swizzles vector to (x,w,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXWY();

	/*
	* GetXWZ
	*
	* swizzles vector to (x,w,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXWZ();

	/*
	* GetXWW
	*
	* swizzles vector to (x,w,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetXWW();

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
	* GetYXW
	*
	* swizzles vector to (y,x,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYXW();

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
	* GetYYW
	*
	* swizzles vector to (y,y,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYYW();

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
	* GetYZW
	*
	* swizzles vector to (y,z,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYZW();

	/*
	* GetYWX
	*
	* swizzles vector to (y,w,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYWX();

	/*
	* GetYWY
	*
	* swizzles vector to (y,w,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYWY();

	/*
	* GetYWZ
	*
	* swizzles vector to (y,w,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYWZ();

	/*
	* GetYWW
	*
	* swizzles vector to (y,w,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetYWW();

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
	* GetZXW
	*
	* swizzles vector to (z,x,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZXW();

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
	* GetZYW
	*
	* swizzles vector to (z,y,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZYW();

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
	* GetZZW
	*
	* swizzles vector to (z,z,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZZW();

	/*
	* GetZWX
	*
	* swizzles vector to (z,w,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZWX();

	/*
	* GetZWY
	*
	* swizzles vector to (z,w,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZWY();

	/*
	* GetZWZ
	*
	* swizzles vector to (z,w,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZWZ();

	/*
	* GetZWW
	*
	* swizzles vector to (z,w,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetZWW();

	/*
	* GetWXX
	*
	* swizzles vector to (w,x,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWXX();

	/*
	* GetWXY
	*
	* swizzles vector to (w,x,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWXY();

	/*
	* GetWXZ
	*
	* swizzles vector to (w,x,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWXZ();

	/*
	* GetWXW
	*
	* swizzles vector to (w,x,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWXW();

	/*
	* GetWYX
	*
	* swizzles vector to (w,y,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWYX();

	/*
	* GetWYY
	*
	* swizzles vector to (w,y,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWYY();

	/*
	* GetWYZ
	*
	* swizzles vector to (w,y,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWYZ();

	/*
	* GetWYW
	*
	* swizzles vector to (w,y,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWYW();

	/*
	* GetWZX
	*
	* swizzles vector to (w,z,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWZX();

	/*
	* GetWZY
	*
	* swizzles vector to (w,z,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWZY();

	/*
	* GetWZZ
	*
	* swizzles vector to (w,z,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWZZ();

	/*
	* GetWZW
	*
	* swizzles vector to (w,z,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWZW();

	/*
	* GetWWX
	*
	* swizzles vector to (w,w,x)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWWX();

	/*
	* GetWWY
	*
	* swizzles vector to (w,w,y)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWWY();

	/*
	* GetWWZ
	*
	* swizzles vector to (w,w,z)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWWZ();

	/*
	* GetWWW
	*
	* swizzles vector to (w,w,w)
	*
	* @returns Vector3T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector3T<T> GetWWW();

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
	* GetXXXW
	*
	* swizzles vector to (x,x,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXXW();

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
	* GetXXYW
	*
	* swizzles vector to (x,x,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXYW();

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
	* GetXXZW
	*
	* swizzles vector to (x,x,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXZW();

	/*
	* GetXXWX
	*
	* swizzles vector to (x,x,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXWX();

	/*
	* GetXXWY
	*
	* swizzles vector to (x,x,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXWY();

	/*
	* GetXXWZ
	*
	* swizzles vector to (x,x,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXWZ();

	/*
	* GetXXWW
	*
	* swizzles vector to (x,x,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXXWW();

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
	* GetXYXW
	*
	* swizzles vector to (x,y,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYXW();

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
	* GetXYYW
	*
	* swizzles vector to (x,y,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYYW();

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
	* GetXYWX
	*
	* swizzles vector to (x,y,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYWX();

	/*
	* GetXYWY
	*
	* swizzles vector to (x,y,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYWY();

	/*
	* GetXYWZ
	*
	* swizzles vector to (x,y,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYWZ();

	/*
	* GetXYWW
	*
	* swizzles vector to (x,y,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXYWW();

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
	* GetXZXW
	*
	* swizzles vector to (x,z,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZXW();

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
	* GetXZYW
	*
	* swizzles vector to (x,z,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZYW();

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
	* GetXZZW
	*
	* swizzles vector to (x,z,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZZW();

	/*
	* GetXZWX
	*
	* swizzles vector to (x,z,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZWX();

	/*
	* GetXZWY
	*
	* swizzles vector to (x,z,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZWY();

	/*
	* GetXZWZ
	*
	* swizzles vector to (x,z,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZWZ();

	/*
	* GetXZWW
	*
	* swizzles vector to (x,z,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXZWW();

	/*
	* GetXWXX
	*
	* swizzles vector to (x,w,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWXX();

	/*
	* GetXWXY
	*
	* swizzles vector to (x,w,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWXY();

	/*
	* GetXWXZ
	*
	* swizzles vector to (x,w,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWXZ();

	/*
	* GetXWXW
	*
	* swizzles vector to (x,w,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWXW();

	/*
	* GetXWYX
	*
	* swizzles vector to (x,w,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWYX();

	/*
	* GetXWYY
	*
	* swizzles vector to (x,w,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWYY();

	/*
	* GetXWYZ
	*
	* swizzles vector to (x,w,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWYZ();

	/*
	* GetXWYW
	*
	* swizzles vector to (x,w,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWYW();

	/*
	* GetXWZX
	*
	* swizzles vector to (x,w,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWZX();

	/*
	* GetXWZY
	*
	* swizzles vector to (x,w,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWZY();

	/*
	* GetXWZZ
	*
	* swizzles vector to (x,w,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWZZ();

	/*
	* GetXWZW
	*
	* swizzles vector to (x,w,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWZW();

	/*
	* GetXWWX
	*
	* swizzles vector to (x,w,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWWX();

	/*
	* GetXWWY
	*
	* swizzles vector to (x,w,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWWY();

	/*
	* GetXWWZ
	*
	* swizzles vector to (x,w,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWWZ();

	/*
	* GetXWWW
	*
	* swizzles vector to (x,w,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetXWWW();

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
	* GetYXXW
	*
	* swizzles vector to (y,x,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXXW();

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
	* GetYXYW
	*
	* swizzles vector to (y,x,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXYW();

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
	* GetYXZW
	*
	* swizzles vector to (y,x,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXZW();

	/*
	* GetYXWX
	*
	* swizzles vector to (y,x,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXWX();

	/*
	* GetYXWY
	*
	* swizzles vector to (y,x,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXWY();

	/*
	* GetYXWZ
	*
	* swizzles vector to (y,x,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXWZ();

	/*
	* GetYXWW
	*
	* swizzles vector to (y,x,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYXWW();

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
	* GetYYXW
	*
	* swizzles vector to (y,y,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYXW();

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
	* GetYYYW
	*
	* swizzles vector to (y,y,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYYW();

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
	* GetYYZW
	*
	* swizzles vector to (y,y,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYZW();

	/*
	* GetYYWX
	*
	* swizzles vector to (y,y,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYWX();

	/*
	* GetYYWY
	*
	* swizzles vector to (y,y,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYWY();

	/*
	* GetYYWZ
	*
	* swizzles vector to (y,y,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYWZ();

	/*
	* GetYYWW
	*
	* swizzles vector to (y,y,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYYWW();

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
	* GetYZXW
	*
	* swizzles vector to (y,z,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZXW();

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
	* GetYZYW
	*
	* swizzles vector to (y,z,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZYW();

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
	* GetYZZW
	*
	* swizzles vector to (y,z,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZZW();

	/*
	* GetYZWX
	*
	* swizzles vector to (y,z,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZWX();

	/*
	* GetYZWY
	*
	* swizzles vector to (y,z,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZWY();

	/*
	* GetYZWZ
	*
	* swizzles vector to (y,z,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZWZ();

	/*
	* GetYZWW
	*
	* swizzles vector to (y,z,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYZWW();

	/*
	* GetYWXX
	*
	* swizzles vector to (y,w,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWXX();

	/*
	* GetYWXY
	*
	* swizzles vector to (y,w,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWXY();

	/*
	* GetYWXZ
	*
	* swizzles vector to (y,w,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWXZ();

	/*
	* GetYWXW
	*
	* swizzles vector to (y,w,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWXW();

	/*
	* GetYWYX
	*
	* swizzles vector to (y,w,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWYX();

	/*
	* GetYWYY
	*
	* swizzles vector to (y,w,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWYY();

	/*
	* GetYWYZ
	*
	* swizzles vector to (y,w,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWYZ();

	/*
	* GetYWYW
	*
	* swizzles vector to (y,w,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWYW();

	/*
	* GetYWZX
	*
	* swizzles vector to (y,w,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWZX();

	/*
	* GetYWZY
	*
	* swizzles vector to (y,w,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWZY();

	/*
	* GetYWZZ
	*
	* swizzles vector to (y,w,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWZZ();

	/*
	* GetYWZW
	*
	* swizzles vector to (y,w,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWZW();

	/*
	* GetYWWX
	*
	* swizzles vector to (y,w,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWWX();

	/*
	* GetYWWY
	*
	* swizzles vector to (y,w,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWWY();

	/*
	* GetYWWZ
	*
	* swizzles vector to (y,w,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWWZ();

	/*
	* GetYWWW
	*
	* swizzles vector to (y,w,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetYWWW();

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
	* GetZXXW
	*
	* swizzles vector to (z,x,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXXW();

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
	* GetZXYW
	*
	* swizzles vector to (z,x,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXYW();

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
	* GetZXZW
	*
	* swizzles vector to (z,x,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXZW();

	/*
	* GetZXWX
	*
	* swizzles vector to (z,x,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXWX();

	/*
	* GetZXWY
	*
	* swizzles vector to (z,x,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXWY();

	/*
	* GetZXWZ
	*
	* swizzles vector to (z,x,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXWZ();

	/*
	* GetZXWW
	*
	* swizzles vector to (z,x,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZXWW();

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
	* GetZYXW
	*
	* swizzles vector to (z,y,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYXW();

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
	* GetZYYW
	*
	* swizzles vector to (z,y,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYYW();

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
	* GetZYZW
	*
	* swizzles vector to (z,y,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYZW();

	/*
	* GetZYWX
	*
	* swizzles vector to (z,y,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYWX();

	/*
	* GetZYWY
	*
	* swizzles vector to (z,y,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYWY();

	/*
	* GetZYWZ
	*
	* swizzles vector to (z,y,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYWZ();

	/*
	* GetZYWW
	*
	* swizzles vector to (z,y,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZYWW();

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
	* GetZZXW
	*
	* swizzles vector to (z,z,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZXW();

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
	* GetZZYW
	*
	* swizzles vector to (z,z,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZYW();

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

	/*
	* GetZZZW
	*
	* swizzles vector to (z,z,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZZW();

	/*
	* GetZZWX
	*
	* swizzles vector to (z,z,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZWX();

	/*
	* GetZZWY
	*
	* swizzles vector to (z,z,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZWY();

	/*
	* GetZZWZ
	*
	* swizzles vector to (z,z,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZWZ();

	/*
	* GetZZWW
	*
	* swizzles vector to (z,z,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZZWW();

	/*
	* GetZWXX
	*
	* swizzles vector to (z,w,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWXX();

	/*
	* GetZWXY
	*
	* swizzles vector to (z,w,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWXY();

	/*
	* GetZWXZ
	*
	* swizzles vector to (z,w,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWXZ();

	/*
	* GetZWXW
	*
	* swizzles vector to (z,w,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWXW();

	/*
	* GetZWYX
	*
	* swizzles vector to (z,w,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWYX();

	/*
	* GetZWYY
	*
	* swizzles vector to (z,w,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWYY();

	/*
	* GetZWYZ
	*
	* swizzles vector to (z,w,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWYZ();

	/*
	* GetZWYW
	*
	* swizzles vector to (z,w,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWYW();

	/*
	* GetZWZX
	*
	* swizzles vector to (z,w,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWZX();

	/*
	* GetZWZY
	*
	* swizzles vector to (z,w,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWZY();

	/*
	* GetZWZZ
	*
	* swizzles vector to (z,w,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWZZ();

	/*
	* GetZWZW
	*
	* swizzles vector to (z,w,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWZW();

	/*
	* GetZWWX
	*
	* swizzles vector to (z,w,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWWX();

	/*
	* GetZWWY
	*
	* swizzles vector to (z,w,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWWY();

	/*
	* GetZWWZ
	*
	* swizzles vector to (z,w,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWWZ();

	/*
	* GetZWWW
	*
	* swizzles vector to (z,w,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetZWWW();

	/*
	* GetWXXX
	*
	* swizzles vector to (w,x,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXXX();

	/*
	* GetWXXY
	*
	* swizzles vector to (w,x,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXXY();

	/*
	* GetWXXZ
	*
	* swizzles vector to (w,x,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXXZ();

	/*
	* GetWXXW
	*
	* swizzles vector to (w,x,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXXW();

	/*
	* GetWXYX
	*
	* swizzles vector to (w,x,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXYX();

	/*
	* GetWXYY
	*
	* swizzles vector to (w,x,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXYY();

	/*
	* GetWXYZ
	*
	* swizzles vector to (w,x,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXYZ();

	/*
	* GetWXYW
	*
	* swizzles vector to (w,x,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXYW();

	/*
	* GetWXZX
	*
	* swizzles vector to (w,x,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXZX();

	/*
	* GetWXZY
	*
	* swizzles vector to (w,x,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXZY();

	/*
	* GetWXZZ
	*
	* swizzles vector to (w,x,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXZZ();

	/*
	* GetWXZW
	*
	* swizzles vector to (w,x,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXZW();

	/*
	* GetWXWX
	*
	* swizzles vector to (w,x,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXWX();

	/*
	* GetWXWY
	*
	* swizzles vector to (w,x,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXWY();

	/*
	* GetWXWZ
	*
	* swizzles vector to (w,x,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXWZ();

	/*
	* GetWXWW
	*
	* swizzles vector to (w,x,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWXWW();

	/*
	* GetWYXX
	*
	* swizzles vector to (w,y,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYXX();

	/*
	* GetWYXY
	*
	* swizzles vector to (w,y,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYXY();

	/*
	* GetWYXZ
	*
	* swizzles vector to (w,y,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYXZ();

	/*
	* GetWYXW
	*
	* swizzles vector to (w,y,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYXW();

	/*
	* GetWYYX
	*
	* swizzles vector to (w,y,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYYX();

	/*
	* GetWYYY
	*
	* swizzles vector to (w,y,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYYY();

	/*
	* GetWYYZ
	*
	* swizzles vector to (w,y,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYYZ();

	/*
	* GetWYYW
	*
	* swizzles vector to (w,y,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYYW();

	/*
	* GetWYZX
	*
	* swizzles vector to (w,y,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYZX();

	/*
	* GetWYZY
	*
	* swizzles vector to (w,y,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYZY();

	/*
	* GetWYZZ
	*
	* swizzles vector to (w,y,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYZZ();

	/*
	* GetWYZW
	*
	* swizzles vector to (w,y,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYZW();

	/*
	* GetWYWX
	*
	* swizzles vector to (w,y,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYWX();

	/*
	* GetWYWY
	*
	* swizzles vector to (w,y,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYWY();

	/*
	* GetWYWZ
	*
	* swizzles vector to (w,y,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYWZ();

	/*
	* GetWYWW
	*
	* swizzles vector to (w,y,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWYWW();

	/*
	* GetWZXX
	*
	* swizzles vector to (w,z,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZXX();

	/*
	* GetWZXY
	*
	* swizzles vector to (w,z,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZXY();

	/*
	* GetWZXZ
	*
	* swizzles vector to (w,z,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZXZ();

	/*
	* GetWZXW
	*
	* swizzles vector to (w,z,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZXW();

	/*
	* GetWZYX
	*
	* swizzles vector to (w,z,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZYX();

	/*
	* GetWZYY
	*
	* swizzles vector to (w,z,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZYY();

	/*
	* GetWZYZ
	*
	* swizzles vector to (w,z,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZYZ();

	/*
	* GetWZYW
	*
	* swizzles vector to (w,z,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZYW();

	/*
	* GetWZZX
	*
	* swizzles vector to (w,z,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZZX();

	/*
	* GetWZZY
	*
	* swizzles vector to (w,z,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZZY();

	/*
	* GetWZZZ
	*
	* swizzles vector to (w,z,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZZZ();

	/*
	* GetWZZW
	*
	* swizzles vector to (w,z,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZZW();

	/*
	* GetWZWX
	*
	* swizzles vector to (w,z,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZWX();

	/*
	* GetWZWY
	*
	* swizzles vector to (w,z,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZWY();

	/*
	* GetWZWZ
	*
	* swizzles vector to (w,z,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZWZ();

	/*
	* GetWZWW
	*
	* swizzles vector to (w,z,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWZWW();

	/*
	* GetWWXX
	*
	* swizzles vector to (w,w,x,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWXX();

	/*
	* GetWWXY
	*
	* swizzles vector to (w,w,x,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWXY();

	/*
	* GetWWXZ
	*
	* swizzles vector to (w,w,x,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWXZ();

	/*
	* GetWWXW
	*
	* swizzles vector to (w,w,x,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWXW();

	/*
	* GetWWYX
	*
	* swizzles vector to (w,w,y,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWYX();

	/*
	* GetWWYY
	*
	* swizzles vector to (w,w,y,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWYY();

	/*
	* GetWWYZ
	*
	* swizzles vector to (w,w,y,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWYZ();

	/*
	* GetWWYW
	*
	* swizzles vector to (w,w,y,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWYW();

	/*
	* GetWWZX
	*
	* swizzles vector to (w,w,z,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWZX();

	/*
	* GetWWZY
	*
	* swizzles vector to (w,w,z,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWZY();

	/*
	* GetWWZZ
	*
	* swizzles vector to (w,w,z,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWZZ();

	/*
	* GetWWZW
	*
	* swizzles vector to (w,w,z,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWZW();

	/*
	* GetWWWX
	*
	* swizzles vector to (w,w,w,x)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWWX();

	/*
	* GetWWWY
	*
	* swizzles vector to (w,w,w,y)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWWY();

	/*
	* GetWWWZ
	*
	* swizzles vector to (w,w,w,z)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWWZ();

	/*
	* GetWWWW
	*
	* swizzles vector to (w,w,w,w)
	*
	* @returns Vector4T<T> - the swizzled vector
	*/
	MATHSLIBRARY_API Vector4T<T> GetWWWW();


	#pragma endregion

};

using Vector4 = Vector4T<float>;

/*
* operator *
* template function
* multiplies a vector by a scalar
*
* @param const float scalar - the number to multiply all components by
* @param const Vector4T<T> vector - the vector to multiply
* @returns Vector4T<T> - the resultant
*/
TEMPLATE
Vector4T<T> operator*(const float scalar, const Vector4T<T> vector);

//multiplication operator (reordered)
TEMPLATE
Vector4T<T> operator*(const float scalar, const Vector4T<T> vector)
{
	return Vector4T<T>{ vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar};
}



/*
* operator /
* template function
* divdes a vector by a scalar
*
* @param const float scalar - the number to divde all components by
* @param const Vector4T<T> vector - the vector to divide
* @returns Vector4T<T> - the resultant
*/
TEMPLATE
Vector4T<T> operator/(const float scalar, const Vector4T<T> vector);

//division operator (reordered)
TEMPLATE
Vector4T<T> operator/(const float scalar, const Vector4T<T> vector)
{
	return Vector4T<T>{ scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar /vector.w};
}



/*
* operator *
* template function
* multiplies a vector by a transformation matrix
*
* @param Matrix4T<T> matrix - the matrix to transform the vector with
* @param Vector4T<T> vector - the vector to copy and apply the transformation to
* @returns Vector4T<T> - the resultant
*/
TEMPLATE
Vector4T<T> operator*(Matrix4T<T> matrix, Vector4T<T> vector);

//matrix transformation (reordered)
TEMPLATE
Vector4T<T> operator*(Matrix4T<T> matrix, Vector4T<T> vector)
{
	Vector4T<T> product = {};

	//a = Vector4T<T> vector passed into the function
	//b = Matrix4 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 4; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 4; i++)
		{
			product[bn] = product[bn] + vector[i] * matrix.mat[i][bn];
		}
	}

	return product;
}
