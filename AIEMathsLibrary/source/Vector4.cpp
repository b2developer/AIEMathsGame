#include "Vector4.h"
#include "Matrix4.h"

#include "Vector2.h"
#include "Vector3.h"

//all of the decimal types
template class Vector4T<float>;
template class Vector4T<double>;
template class Vector4T<long double>;

//subscript operator
TEMPLATE
T & Vector4T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default: throw;
	}
}

//cast to T pointer operator
TEMPLATE
Vector4T<T>::operator T*()
{
	return &x;
}

//cast to vector2
TEMPLATE
Vector4T<T>::operator Vector2T<T>() 
{
	return Vector2T<T>{x, y};
}

//cast to vector3
TEMPLATE
Vector4T<T>::operator Vector3T<T>()
{
	return Vector3T<T>{x, y, z};
}

//addition operator
TEMPLATE
Vector4T<T> Vector4T<T>::operator+(const Vector4T<T> other)
{
	return Vector4T<T>{ x + other.x, y + other.y, z + other.z , w + other.w };
}

TEMPLATE
void Vector4T<T>::operator+=(const Vector4T<T> other)
{
	*this = Vector4T<T>{ x + other.x, y + other.y, z + other.z, w + other.w };
}
//subtraction operator
TEMPLATE
Vector4T<T> Vector4T<T>::operator-(const Vector4T<T> other)
{
	return Vector4T<T>{ x - other.x, y - other.y, z - other.z, w - other.w };
}

//multiplication operator
TEMPLATE
Vector4T<T> Vector4T<T>::operator*(const T scalar)
{
	return Vector4T<T>{ x * scalar, y * scalar, z * scalar, w * scalar };
}

//division operator
TEMPLATE
Vector4T<T> Vector4T<T>::operator/(const T scalar)
{
	return Vector4T<T>{ x / scalar, y / scalar, z * scalar, w * scalar };
}

//dot product
TEMPLATE
T Vector4T<T>::dot(const Vector4T<T> other)
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

//squared magnitude calculation
TEMPLATE
T Vector4T<T>::sqrMagnitude()
{
	return x * x + y * y + z * z + w * w;
}

//magnitude calculation
TEMPLATE
T Vector4T<T>::magnitude()
{
	return (T)sqrt(sqrMagnitude());
}

//normalise the vector
TEMPLATE
void Vector4T<T>::normalise()
{
	T mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}

//calculate the normalised vector
TEMPLATE
Vector4T<T> Vector4T<T>::normalised()
{
	T mag = magnitude();

	if (mag == 0)
	{
		return Vector4T<T>{};
	}
	else
	{
		return Vector4T<T>{ x / mag, y / mag, z / mag, w / mag};
	}
}

//calculate the perpendicular vector to two others
TEMPLATE
Vector4T<T> Vector4T<T>::cross(const Vector4T<T> other)
{
	return Vector4T<T>{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0 };
}

//matrix transformation
TEMPLATE
Vector4T<T> Vector4T<T>::operator*(Matrix4T<T> matrix)
{
	Vector4T<T> product = {};

	//a = Vector that this function is passing through
	//b = Matrix4 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 4; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 4; i++)
		{
			product[bn] = product[bn] + (*this)[i] * matrix.mat[i][bn];
		}
	}

	return product;
}

#pragma region swizzling
//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetXX()
{
	return Vector2T<T>{x, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetXY()
{
	return Vector2T<T>{x, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetXZ()
{
	return Vector2T<T>{x, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetXW()
{
	return Vector2T<T>{x, w};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetYX()
{
	return Vector2T<T>{y, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetYY()
{
	return Vector2T<T>{y, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetYZ()
{
	return Vector2T<T>{y, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetYW()
{
	return Vector2T<T>{y, w};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetZX()
{
	return Vector2T<T>{z, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetZY()
{
	return Vector2T<T>{z, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetZZ()
{
	return Vector2T<T>{z, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetZW()
{
	return Vector2T<T>{z, w};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetWX()
{
	return Vector2T<T>{w, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetWY()
{
	return Vector2T<T>{w, y};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetWZ()
{
	return Vector2T<T>{w, z};
}

//swizzling
TEMPLATE
Vector2T<T> Vector4T<T>::GetWW()
{
	return Vector2T<T>{w, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXXX()
{
	return Vector3T<T>{x, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXXY()
{
	return Vector3T<T>{x, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXXZ()
{
	return Vector3T<T>{x, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXXW()
{
	return Vector3T<T>{x, x, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXYX()
{
	return Vector3T<T>{x, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXYY()
{
	return Vector3T<T>{x, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXYZ()
{
	return Vector3T<T>{x, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXYW()
{
	return Vector3T<T>{x, y, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXZX()
{
	return Vector3T<T>{x, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXZY()
{
	return Vector3T<T>{x, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXZZ()
{
	return Vector3T<T>{x, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXZW()
{
	return Vector3T<T>{x, z, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXWX()
{
	return Vector3T<T>{x, w, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXWY()
{
	return Vector3T<T>{x, w, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXWZ()
{
	return Vector3T<T>{x, w, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetXWW()
{
	return Vector3T<T>{x, w, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYXX()
{
	return Vector3T<T>{y, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYXY()
{
	return Vector3T<T>{y, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYXZ()
{
	return Vector3T<T>{y, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYXW()
{
	return Vector3T<T>{y, x, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYYX()
{
	return Vector3T<T>{y, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYYY()
{
	return Vector3T<T>{y, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYYZ()
{
	return Vector3T<T>{y, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYYW()
{
	return Vector3T<T>{y, y, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYZX()
{
	return Vector3T<T>{y, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYZY()
{
	return Vector3T<T>{y, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYZZ()
{
	return Vector3T<T>{y, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYZW()
{
	return Vector3T<T>{y, z, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYWX()
{
	return Vector3T<T>{y, w, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYWY()
{
	return Vector3T<T>{y, w, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYWZ()
{
	return Vector3T<T>{y, w, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetYWW()
{
	return Vector3T<T>{y, w, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZXX()
{
	return Vector3T<T>{z, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZXY()
{
	return Vector3T<T>{z, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZXZ()
{
	return Vector3T<T>{z, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZXW()
{
	return Vector3T<T>{z, x, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZYX()
{
	return Vector3T<T>{z, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZYY()
{
	return Vector3T<T>{z, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZYZ()
{
	return Vector3T<T>{z, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZYW()
{
	return Vector3T<T>{z, y, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZZX()
{
	return Vector3T<T>{z, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZZY()
{
	return Vector3T<T>{z, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZZZ()
{
	return Vector3T<T>{z, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZZW()
{
	return Vector3T<T>{z, z, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZWX()
{
	return Vector3T<T>{z, w, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZWY()
{
	return Vector3T<T>{z, w, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZWZ()
{
	return Vector3T<T>{z, w, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetZWW()
{
	return Vector3T<T>{z, w, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWXX()
{
	return Vector3T<T>{w, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWXY()
{
	return Vector3T<T>{w, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWXZ()
{
	return Vector3T<T>{w, x, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWXW()
{
	return Vector3T<T>{w, x, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWYX()
{
	return Vector3T<T>{w, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWYY()
{
	return Vector3T<T>{w, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWYZ()
{
	return Vector3T<T>{w, y, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWYW()
{
	return Vector3T<T>{w, y, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWZX()
{
	return Vector3T<T>{w, z, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWZY()
{
	return Vector3T<T>{w, z, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWZZ()
{
	return Vector3T<T>{w, z, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWZW()
{
	return Vector3T<T>{w, z, w};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWWX()
{
	return Vector3T<T>{w, w, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWWY()
{
	return Vector3T<T>{w, w, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWWZ()
{
	return Vector3T<T>{w, w, z};
}

//swizzling
TEMPLATE
Vector3T<T> Vector4T<T>::GetWWW()
{
	return Vector3T<T>{w, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXXX()
{
	return Vector4T<T>{x, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXXY()
{
	return Vector4T<T>{x, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXXZ()
{
	return Vector4T<T>{x, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXXW()
{
	return Vector4T<T>{x, x, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXYX()
{
	return Vector4T<T>{x, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXYY()
{
	return Vector4T<T>{x, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXYZ()
{
	return Vector4T<T>{x, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXYW()
{
	return Vector4T<T>{x, x, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXZX()
{
	return Vector4T<T>{x, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXZY()
{
	return Vector4T<T>{x, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXZZ()
{
	return Vector4T<T>{x, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXZW()
{
	return Vector4T<T>{x, x, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXWX()
{
	return Vector4T<T>{x, x, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXWY()
{
	return Vector4T<T>{x, x, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXWZ()
{
	return Vector4T<T>{x, x, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXXWW()
{
	return Vector4T<T>{x, x, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYXX()
{
	return Vector4T<T>{x, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYXY()
{
	return Vector4T<T>{x, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYXZ()
{
	return Vector4T<T>{x, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYXW()
{
	return Vector4T<T>{x, y, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYYX()
{
	return Vector4T<T>{x, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYYY()
{
	return Vector4T<T>{x, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYYZ()
{
	return Vector4T<T>{x, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYYW()
{
	return Vector4T<T>{x, y, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYZX()
{
	return Vector4T<T>{x, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYZY()
{
	return Vector4T<T>{x, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYZZ()
{
	return Vector4T<T>{x, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYWX()
{
	return Vector4T<T>{x, y, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYWY()
{
	return Vector4T<T>{x, y, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYWZ()
{
	return Vector4T<T>{x, y, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXYWW()
{
	return Vector4T<T>{x, y, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZXX()
{
	return Vector4T<T>{x, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZXY()
{
	return Vector4T<T>{x, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZXZ()
{
	return Vector4T<T>{x, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZXW()
{
	return Vector4T<T>{x, z, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZYX()
{
	return Vector4T<T>{x, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZYY()
{
	return Vector4T<T>{x, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZYZ()
{
	return Vector4T<T>{x, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZYW()
{
	return Vector4T<T>{x, z, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZZX()
{
	return Vector4T<T>{x, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZZY()
{
	return Vector4T<T>{x, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZZZ()
{
	return Vector4T<T>{x, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZZW()
{
	return Vector4T<T>{x, z, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZWX()
{
	return Vector4T<T>{x, z, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZWY()
{
	return Vector4T<T>{x, z, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZWZ()
{
	return Vector4T<T>{x, z, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXZWW()
{
	return Vector4T<T>{x, z, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWXX()
{
	return Vector4T<T>{x, w, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWXY()
{
	return Vector4T<T>{x, w, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWXZ()
{
	return Vector4T<T>{x, w, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWXW()
{
	return Vector4T<T>{x, w, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWYX()
{
	return Vector4T<T>{x, w, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWYY()
{
	return Vector4T<T>{x, w, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWYZ()
{
	return Vector4T<T>{x, w, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWYW()
{
	return Vector4T<T>{x, w, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWZX()
{
	return Vector4T<T>{x, w, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWZY()
{
	return Vector4T<T>{x, w, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWZZ()
{
	return Vector4T<T>{x, w, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWZW()
{
	return Vector4T<T>{x, w, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWWX()
{
	return Vector4T<T>{x, w, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWWY()
{
	return Vector4T<T>{x, w, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWWZ()
{
	return Vector4T<T>{x, w, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetXWWW()
{
	return Vector4T<T>{x, w, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXXX()
{
	return Vector4T<T>{y, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXXY()
{
	return Vector4T<T>{y, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXXZ()
{
	return Vector4T<T>{y, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXXW()
{
	return Vector4T<T>{y, x, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXYX()
{
	return Vector4T<T>{y, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXYY()
{
	return Vector4T<T>{y, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXYZ()
{
	return Vector4T<T>{y, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXYW()
{
	return Vector4T<T>{y, x, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXZX()
{
	return Vector4T<T>{y, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXZY()
{
	return Vector4T<T>{y, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXZZ()
{
	return Vector4T<T>{y, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXZW()
{
	return Vector4T<T>{y, x, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXWX()
{
	return Vector4T<T>{y, x, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXWY()
{
	return Vector4T<T>{y, x, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXWZ()
{
	return Vector4T<T>{y, x, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYXWW()
{
	return Vector4T<T>{y, x, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYXX()
{
	return Vector4T<T>{y, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYXY()
{
	return Vector4T<T>{y, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYXZ()
{
	return Vector4T<T>{y, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYXW()
{
	return Vector4T<T>{y, y, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYYX()
{
	return Vector4T<T>{y, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYYY()
{
	return Vector4T<T>{y, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYYZ()
{
	return Vector4T<T>{y, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYYW()
{
	return Vector4T<T>{y, y, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYZX()
{
	return Vector4T<T>{y, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYZY()
{
	return Vector4T<T>{y, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYZZ()
{
	return Vector4T<T>{y, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYZW()
{
	return Vector4T<T>{y, y, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYWX()
{
	return Vector4T<T>{y, y, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYWY()
{
	return Vector4T<T>{y, y, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYWZ()
{
	return Vector4T<T>{y, y, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYYWW()
{
	return Vector4T<T>{y, y, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZXX()
{
	return Vector4T<T>{y, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZXY()
{
	return Vector4T<T>{y, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZXZ()
{
	return Vector4T<T>{y, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZXW()
{
	return Vector4T<T>{y, z, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZYX()
{
	return Vector4T<T>{y, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZYY()
{
	return Vector4T<T>{y, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZYZ()
{
	return Vector4T<T>{y, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZYW()
{
	return Vector4T<T>{y, z, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZZX()
{
	return Vector4T<T>{y, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZZY()
{
	return Vector4T<T>{y, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZZZ()
{
	return Vector4T<T>{y, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZZW()
{
	return Vector4T<T>{y, z, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZWX()
{
	return Vector4T<T>{y, z, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZWY()
{
	return Vector4T<T>{y, z, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZWZ()
{
	return Vector4T<T>{y, z, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYZWW()
{
	return Vector4T<T>{y, z, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWXX()
{
	return Vector4T<T>{y, w, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWXY()
{
	return Vector4T<T>{y, w, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWXZ()
{
	return Vector4T<T>{y, w, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWXW()
{
	return Vector4T<T>{y, w, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWYX()
{
	return Vector4T<T>{y, w, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWYY()
{
	return Vector4T<T>{y, w, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWYZ()
{
	return Vector4T<T>{y, w, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWYW()
{
	return Vector4T<T>{y, w, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWZX()
{
	return Vector4T<T>{y, w, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWZY()
{
	return Vector4T<T>{y, w, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWZZ()
{
	return Vector4T<T>{y, w, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWZW()
{
	return Vector4T<T>{y, w, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWWX()
{
	return Vector4T<T>{y, w, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWWY()
{
	return Vector4T<T>{y, w, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWWZ()
{
	return Vector4T<T>{y, w, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetYWWW()
{
	return Vector4T<T>{y, w, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXXX()
{
	return Vector4T<T>{z, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXXY()
{
	return Vector4T<T>{z, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXXZ()
{
	return Vector4T<T>{z, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXXW()
{
	return Vector4T<T>{z, x, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXYX()
{
	return Vector4T<T>{z, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXYY()
{
	return Vector4T<T>{z, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXYZ()
{
	return Vector4T<T>{z, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXYW()
{
	return Vector4T<T>{z, x, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXZX()
{
	return Vector4T<T>{z, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXZY()
{
	return Vector4T<T>{z, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXZZ()
{
	return Vector4T<T>{z, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXZW()
{
	return Vector4T<T>{z, x, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXWX()
{
	return Vector4T<T>{z, x, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXWY()
{
	return Vector4T<T>{z, x, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXWZ()
{
	return Vector4T<T>{z, x, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZXWW()
{
	return Vector4T<T>{z, x, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYXX()
{
	return Vector4T<T>{z, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYXY()
{
	return Vector4T<T>{z, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYXZ()
{
	return Vector4T<T>{z, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYXW()
{
	return Vector4T<T>{z, y, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYYX()
{
	return Vector4T<T>{z, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYYY()
{
	return Vector4T<T>{z, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYYZ()
{
	return Vector4T<T>{z, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYYW()
{
	return Vector4T<T>{z, y, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYZX()
{
	return Vector4T<T>{z, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYZY()
{
	return Vector4T<T>{z, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYZZ()
{
	return Vector4T<T>{z, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYZW()
{
	return Vector4T<T>{z, y, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYWX()
{
	return Vector4T<T>{z, y, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYWY()
{
	return Vector4T<T>{z, y, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYWZ()
{
	return Vector4T<T>{z, y, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZYWW()
{
	return Vector4T<T>{z, y, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZXX()
{
	return Vector4T<T>{z, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZXY()
{
	return Vector4T<T>{z, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZXZ()
{
	return Vector4T<T>{z, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZXW()
{
	return Vector4T<T>{z, z, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZYX()
{
	return Vector4T<T>{z, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZYY()
{
	return Vector4T<T>{z, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZYZ()
{
	return Vector4T<T>{z, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZYW()
{
	return Vector4T<T>{z, z, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZZX()
{
	return Vector4T<T>{z, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZZY()
{
	return Vector4T<T>{z, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZZZ()
{
	return Vector4T<T>{z, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZZW()
{
	return Vector4T<T>{z, z, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZWX()
{
	return Vector4T<T>{z, z, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZWY()
{
	return Vector4T<T>{z, z, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZWZ()
{
	return Vector4T<T>{z, z, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZZWW()
{
	return Vector4T<T>{z, z, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWXX()
{
	return Vector4T<T>{z, w, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWXY()
{
	return Vector4T<T>{z, w, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWXZ()
{
	return Vector4T<T>{z, w, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWXW()
{
	return Vector4T<T>{z, w, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWYX()
{
	return Vector4T<T>{z, w, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWYY()
{
	return Vector4T<T>{z, w, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWYZ()
{
	return Vector4T<T>{z, w, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWYW()
{
	return Vector4T<T>{z, w, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWZX()
{
	return Vector4T<T>{z, w, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWZY()
{
	return Vector4T<T>{z, w, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWZZ()
{
	return Vector4T<T>{z, w, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWZW()
{
	return Vector4T<T>{z, w, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWWX()
{
	return Vector4T<T>{z, w, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWWY()
{
	return Vector4T<T>{z, w, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWWZ()
{
	return Vector4T<T>{z, w, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetZWWW()
{
	return Vector4T<T>{z, w, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXXX()
{
	return Vector4T<T>{w, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXXY()
{
	return Vector4T<T>{w, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXXZ()
{
	return Vector4T<T>{w, x, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXXW()
{
	return Vector4T<T>{w, x, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXYX()
{
	return Vector4T<T>{w, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXYY()
{
	return Vector4T<T>{w, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXYZ()
{
	return Vector4T<T>{w, x, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXYW()
{
	return Vector4T<T>{w, x, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXZX()
{
	return Vector4T<T>{w, x, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXZY()
{
	return Vector4T<T>{w, x, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXZZ()
{
	return Vector4T<T>{w, x, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXZW()
{
	return Vector4T<T>{w, x, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXWX()
{
	return Vector4T<T>{w, x, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXWY()
{
	return Vector4T<T>{w, x, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXWZ()
{
	return Vector4T<T>{w, x, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWXWW()
{
	return Vector4T<T>{w, x, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYXX()
{
	return Vector4T<T>{w, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYXY()
{
	return Vector4T<T>{w, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYXZ()
{
	return Vector4T<T>{w, y, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYXW()
{
	return Vector4T<T>{w, y, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYYX()
{
	return Vector4T<T>{w, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYYY()
{
	return Vector4T<T>{w, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYYZ()
{
	return Vector4T<T>{w, y, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYYW()
{
	return Vector4T<T>{w, y, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYZX()
{
	return Vector4T<T>{w, y, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYZY()
{
	return Vector4T<T>{w, y, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYZZ()
{
	return Vector4T<T>{w, y, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYZW()
{
	return Vector4T<T>{w, y, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYWX()
{
	return Vector4T<T>{w, y, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYWY()
{
	return Vector4T<T>{w, y, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYWZ()
{
	return Vector4T<T>{w, y, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWYWW()
{
	return Vector4T<T>{w, y, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZXX()
{
	return Vector4T<T>{w, z, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZXY()
{
	return Vector4T<T>{w, z, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZXZ()
{
	return Vector4T<T>{w, z, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZXW()
{
	return Vector4T<T>{w, z, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZYX()
{
	return Vector4T<T>{w, z, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZYY()
{
	return Vector4T<T>{w, z, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZYZ()
{
	return Vector4T<T>{w, z, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZYW()
{
	return Vector4T<T>{w, z, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZZX()
{
	return Vector4T<T>{w, z, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZZY()
{
	return Vector4T<T>{w, z, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZZZ()
{
	return Vector4T<T>{w, z, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZZW()
{
	return Vector4T<T>{w, z, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZWX()
{
	return Vector4T<T>{w, z, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZWY()
{
	return Vector4T<T>{w, z, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZWZ()
{
	return Vector4T<T>{w, z, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWZWW()
{
	return Vector4T<T>{w, z, w, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWXX()
{
	return Vector4T<T>{w, w, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWXY()
{
	return Vector4T<T>{w, w, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWXZ()
{
	return Vector4T<T>{w, w, x, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWXW()
{
	return Vector4T<T>{w, w, x, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWYX()
{
	return Vector4T<T>{w, w, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWYY()
{
	return Vector4T<T>{w, w, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWYZ()
{
	return Vector4T<T>{w, w, y, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWYW()
{
	return Vector4T<T>{w, w, y, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWZX()
{
	return Vector4T<T>{w, w, z, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWZY()
{
	return Vector4T<T>{w, w, z, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWZZ()
{
	return Vector4T<T>{w, w, z, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWZW()
{
	return Vector4T<T>{w, w, z, w};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWWX()
{
	return Vector4T<T>{w, w, w, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWWY()
{
	return Vector4T<T>{w, w, w, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWWZ()
{
	return Vector4T<T>{w, w, w, z};
}

//swizzling
TEMPLATE
Vector4T<T> Vector4T<T>::GetWWWW()
{
	return Vector4T<T>{w, w, w, w};
}


#pragma endregion

