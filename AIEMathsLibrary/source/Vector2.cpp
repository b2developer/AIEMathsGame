#include "Vector2.h"
#include "Matrix2.h"

#include "Vector3.h"
#include "Vector4.h"

//all of the decimal types
template class Vector2T<float>;
template class Vector2T<double>;
template class Vector2T<long double>;

//subscript operator
TEMPLATE
T & Vector2T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	default: throw;
	} 
}

//cast to T pointer operator
TEMPLATE
Vector2T<T>::operator T*()
{
	return &x;
}

//cast to vector3
TEMPLATE
Vector2T<T>::operator Vector3T<T>()
{
	return Vector3T<T>{x, y, 0.0f};
}

//cast to vector4
TEMPLATE
Vector2T<T>::operator Vector4T<T>()
{
	return Vector4T<T>{x, y, 0.0f, 0.0f};
}

//addition operator
TEMPLATE
Vector2T<T> Vector2T<T>::operator+(const Vector2T<T> other)
{
	return Vector2T<T>{ x + other.x, y + other.y };
}

TEMPLATE
void Vector2T<T>::operator+=(const Vector2T<T> other)
{
	*this = Vector2T<T>{ x + other.x, y + other.y };
}

//subtraction operator
TEMPLATE
Vector2T<T> Vector2T<T>::operator-(const Vector2T<T> other)
{
	return Vector2T<T>{ x - other.x, y - other.y };
}

//multiplication operator
TEMPLATE
Vector2T<T> Vector2T<T>::operator*(const T scalar)
{
	return Vector2T<T>{ x * scalar, y * scalar };
}

//division operator
TEMPLATE
Vector2T<T> Vector2T<T>::operator/(const T scalar)
{
	return Vector2T<T>{ x / scalar, y / scalar };
}

//dot product
TEMPLATE
T Vector2T<T>::dot(const Vector2T<T> other)
{
	return x * other.x + y * other.y;
}

//squared magnitude calculation
TEMPLATE
T Vector2T<T>::sqrMagnitude()
{
	return x * x + y * y;
}

//magnitude calculation
TEMPLATE
T Vector2T<T>::magnitude()
{
	return (T)sqrt(sqrMagnitude());
}

//normalise the vector
TEMPLATE
void Vector2T<T>::normalise()
{
	T mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
	}
}

//calculate the normalised vector
TEMPLATE
Vector2T<T> Vector2T<T>::normalised()
{
	T mag = magnitude();

	if (mag == 0)
	{
		return Vector2T<T>{};
	}
	else
	{
		return Vector2T<T>{ x / mag, y / mag };
	}
}

//matrix transformation
TEMPLATE
Vector2T<T> Vector2T<T>::operator*(Matrix2T<T> matrix)
{
	Vector2T<T> product = {};

	//a = Vector that this function is passing through
	//b = Matrix2 matrix passed into the function

	//iterate across b's columns and a's rows
	for (int bn = 0; bn < 2; bn++)
	{
		//iterate across a's rows and b's columns
		for (int i = 0; i < 2; i++)
		{
			product[bn] = product[bn] + (*this)[i] * matrix.mat[i][bn];
		}
	}

	return product;
}

//normal calculation
TEMPLATE
Vector2T<T> Vector2T<T>::normal(NormalDirection direction)
{
	switch (direction)
	{
	case NormalDirection::LEFT: return Vector2T<T>{-y, x};
	case NormalDirection::RIGHT:return Vector2T<T>{y, -x};
	default: throw; //this is impossible
	}
}

//get the rotation represented by the vector
TEMPLATE
T Vector2T<T>::getRotation()
{
	//atan2 achieves this
	return (T)atan2(y, x);
}

#pragma region swizzling
//swizzling
TEMPLATE
Vector2T<T> Vector2T<T>::GetXX()
{
	return Vector2T<T>{x, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector2T<T>::GetYX()
{
	return Vector2T<T>{y, x};
}

//swizzling
TEMPLATE
Vector2T<T> Vector2T<T>::GetYY()
{
	return Vector2T<T>{y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetXXX()
{
	return Vector3T<T>{x, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetXXY()
{
	return Vector3T<T>{x, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetXYX()
{
	return Vector3T<T>{x, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetXYY()
{
	return Vector3T<T>{x, y, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetYXX()
{
	return Vector3T<T>{y, x, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetYXY()
{
	return Vector3T<T>{y, x, y};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetYYX()
{
	return Vector3T<T>{y, y, x};
}

//swizzling
TEMPLATE
Vector3T<T> Vector2T<T>::GetYYY()
{
	return Vector3T<T>{y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXXXX()
{
	return Vector4T<T>{x, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXXXY()
{
	return Vector4T<T>{x, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXXYX()
{
	return Vector4T<T>{x, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXXYY()
{
	return Vector4T<T>{x, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXYXX()
{
	return Vector4T<T>{x, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXYXY()
{
	return Vector4T<T>{x, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXYYX()
{
	return Vector4T<T>{x, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetXYYY()
{
	return Vector4T<T>{x, y, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYXXX()
{
	return Vector4T<T>{y, x, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYXXY()
{
	return Vector4T<T>{y, x, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYXYX()
{
	return Vector4T<T>{y, x, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYXYY()
{
	return Vector4T<T>{y, x, y, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYYXX()
{
	return Vector4T<T>{y, y, x, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYYXY()
{
	return Vector4T<T>{y, y, x, y};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYYYX()
{
	return Vector4T<T>{y, y, y, x};
}

//swizzling
TEMPLATE
Vector4T<T> Vector2T<T>::GetYYYY()
{
	return Vector4T<T>{y, y, y, y};
}


#pragma endregion
