#include "Vector3.h"
#include "Matrix3.h"

#include "Vector2.h"
#include "Vector4.h"

//all of the decimal types
template class Vector3T<float>;
template class Vector3T<double>;
template class Vector3T<long double>;

//subscript operator
TEMPLATE
T & Vector3T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: throw;
	}
}

//cast to T pointer operator
TEMPLATE
Vector3T<T>::operator T*()
{
	return &x;
}

//cast to vector2
TEMPLATE
Vector3T<T>::operator Vector2T<T>()
{
	return Vector2T<T>{x, y};
}

//cast to vector4
TEMPLATE
Vector3T<T>::operator Vector4T<T>()
{
	return Vector4T<T>{x, y, z, 0.0f};
}

//addition operator
TEMPLATE
Vector3T<T> Vector3T<T>::operator+(const Vector3T<T> other)
{
	return Vector3T<T>{ x + other.x, y + other.y, z + other.z};
}

TEMPLATE
void Vector3T<T>::operator+=(const Vector3T<T> other)
{
	*this = Vector3T<T>{ x + other.x, y + other.y, z + other.z};
}


//subtraction operator
TEMPLATE
Vector3T<T> Vector3T<T>::operator-(const Vector3T<T> other)
{
	return Vector3T<T>{ x - other.x, y - other.y, z - other.z};
}

//multiplication operator
TEMPLATE
Vector3T<T> Vector3T<T>::operator*(const T scalar)
{
	return Vector3T<T>{ x * scalar, y * scalar, z * scalar };
}

//division operator
TEMPLATE
Vector3T<T> Vector3T<T>::operator/(const T scalar)
{
	return Vector3T<T>{ x / scalar, y / scalar, z * scalar };
}

//dot product
TEMPLATE
T Vector3T<T>::dot(const Vector3T<T> other)
{
	return x * other.x + y * other.y + z * other.z;
}

//squared magnitude calculation
TEMPLATE
T Vector3T<T>::sqrMagnitude()
{
	return x * x + y * y + z * z;
}

//magnitude calculation
TEMPLATE
T Vector3T<T>::magnitude()
{
	return (T)sqrt(sqrMagnitude());
}

//normalise the vector
TEMPLATE
void Vector3T<T>::normalise()
{
	T mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

//calculate the normalised vector
TEMPLATE
Vector3T<T> Vector3T<T>::normalised()
{
	T mag = magnitude();

	if (mag == 0)
	{
		return Vector3T<T>{};
	}
	else
	{
		return Vector3T<T>{ x / mag, y / mag, z / mag};
	}
}

//calculate the perpendicular vector to two others
TEMPLATE
Vector3T<T> Vector3T<T>::cross(const Vector3T<T> other)
{
	return Vector3T<T>{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
}

//matrix transformation
TEMPLATE
Vector3T<T> Vector3T<T>::operator*(Matrix3T<T> matrix)
{
	Vector3T<T> product = {};

	//a = Vector that this function is passing through
	//b = Matrix3 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 3; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 3; i++)
		{
			product[bn] = product[bn] + (*this)[i] * matrix.mat[i][bn];
		}
	}

	return product;
}

#pragma region swizzling
//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetXX()
{
	return Vector2T<T>{x, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetXY()
{
	return Vector2T<T>{x, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetXZ()
{
	return Vector2T<T>{x, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetYX()
{
	return Vector2T<T>{y, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetYY()
{
	return Vector2T<T>{y, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetYZ()
{
	return Vector2T<T>{y, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetZX()
{
	return Vector2T<T>{z, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetZY()
{
	return Vector2T<T>{z, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector3T<T>::GetZZ()
{
	return Vector2T<T>{z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXXX()
{
	return Vector3T<T>{x, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXXY()
{
	return Vector3T<T>{x, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXXZ()
{
	return Vector3T<T>{x, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXYX()
{
	return Vector3T<T>{x, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXYY()
{
	return Vector3T<T>{x, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXZX()
{
	return Vector3T<T>{x, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXZY()
{
	return Vector3T<T>{x, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetXZZ()
{
	return Vector3T<T>{x, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYXX()
{
	return Vector3T<T>{y, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYXY()
{
	return Vector3T<T>{y, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYXZ()
{
	return Vector3T<T>{y, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYYX()
{
	return Vector3T<T>{y, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYYY()
{
	return Vector3T<T>{y, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYYZ()
{
	return Vector3T<T>{y, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYZX()
{
	return Vector3T<T>{y, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYZY()
{
	return Vector3T<T>{y, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetYZZ()
{
	return Vector3T<T>{y, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZXX()
{
	return Vector3T<T>{z, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZXY()
{
	return Vector3T<T>{z, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZXZ()
{
	return Vector3T<T>{z, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZYX()
{
	return Vector3T<T>{z, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZYY()
{
	return Vector3T<T>{z, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZYZ()
{
	return Vector3T<T>{z, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZZX()
{
	return Vector3T<T>{z, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZZY()
{
	return Vector3T<T>{z, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector3T<T>::GetZZZ()
{
	return Vector3T<T>{z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXXX()
{
	return Vector4T<T>{x, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXXY()
{
	return Vector4T<T>{x, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXXZ()
{
	return Vector4T<T>{x, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXYX()
{
	return Vector4T<T>{x, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXYY()
{
	return Vector4T<T>{x, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXYZ()
{
	return Vector4T<T>{x, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXZX()
{
	return Vector4T<T>{x, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXZY()
{
	return Vector4T<T>{x, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXXZZ()
{
	return Vector4T<T>{x, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYXX()
{
	return Vector4T<T>{x, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYXY()
{
	return Vector4T<T>{x, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYXZ()
{
	return Vector4T<T>{x, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYYX()
{
	return Vector4T<T>{x, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYYY()
{
	return Vector4T<T>{x, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYYZ()
{
	return Vector4T<T>{x, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYZX()
{
	return Vector4T<T>{x, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYZY()
{
	return Vector4T<T>{x, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXYZZ()
{
	return Vector4T<T>{x, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZXX()
{
	return Vector4T<T>{x, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZXY()
{
	return Vector4T<T>{x, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZXZ()
{
	return Vector4T<T>{x, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZYX()
{
	return Vector4T<T>{x, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZYY()
{
	return Vector4T<T>{x, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZYZ()
{
	return Vector4T<T>{x, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZZX()
{
	return Vector4T<T>{x, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZZY()
{
	return Vector4T<T>{x, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetXZZZ()
{
	return Vector4T<T>{x, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXXX()
{
	return Vector4T<T>{y, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXXY()
{
	return Vector4T<T>{y, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXXZ()
{
	return Vector4T<T>{y, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXYX()
{
	return Vector4T<T>{y, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXYY()
{
	return Vector4T<T>{y, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXYZ()
{
	return Vector4T<T>{y, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXZX()
{
	return Vector4T<T>{y, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXZY()
{
	return Vector4T<T>{y, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYXZZ()
{
	return Vector4T<T>{y, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYXX()
{
	return Vector4T<T>{y, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYXY()
{
	return Vector4T<T>{y, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYXZ()
{
	return Vector4T<T>{y, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYYX()
{
	return Vector4T<T>{y, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYYY()
{
	return Vector4T<T>{y, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYYZ()
{
	return Vector4T<T>{y, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYZX()
{
	return Vector4T<T>{y, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYZY()
{
	return Vector4T<T>{y, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYYZZ()
{
	return Vector4T<T>{y, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZXX()
{
	return Vector4T<T>{y, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZXY()
{
	return Vector4T<T>{y, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZXZ()
{
	return Vector4T<T>{y, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZYX()
{
	return Vector4T<T>{y, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZYY()
{
	return Vector4T<T>{y, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZYZ()
{
	return Vector4T<T>{y, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZZX()
{
	return Vector4T<T>{y, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZZY()
{
	return Vector4T<T>{y, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetYZZZ()
{
	return Vector4T<T>{y, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXXX()
{
	return Vector4T<T>{z, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXXY()
{
	return Vector4T<T>{z, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXXZ()
{
	return Vector4T<T>{z, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXYX()
{
	return Vector4T<T>{z, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXYY()
{
	return Vector4T<T>{z, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXYZ()
{
	return Vector4T<T>{z, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXZX()
{
	return Vector4T<T>{z, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXZY()
{
	return Vector4T<T>{z, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZXZZ()
{
	return Vector4T<T>{z, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYXX()
{
	return Vector4T<T>{z, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYXY()
{
	return Vector4T<T>{z, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYXZ()
{
	return Vector4T<T>{z, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYYX()
{
	return Vector4T<T>{z, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYYY()
{
	return Vector4T<T>{z, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYYZ()
{
	return Vector4T<T>{z, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYZX()
{
	return Vector4T<T>{z, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYZY()
{
	return Vector4T<T>{z, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZYZZ()
{
	return Vector4T<T>{z, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZXX()
{
	return Vector4T<T>{z, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZXY()
{
	return Vector4T<T>{z, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZXZ()
{
	return Vector4T<T>{z, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZYX()
{
	return Vector4T<T>{z, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZYY()
{
	return Vector4T<T>{z, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZYZ()
{
	return Vector4T<T>{z, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZZX()
{
	return Vector4T<T>{z, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZZY()
{
	return Vector4T<T>{z, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector3T<T>::GetZZZZ()
{
	return Vector4T<T>{z, z, z, z};
}


#pragma endregion