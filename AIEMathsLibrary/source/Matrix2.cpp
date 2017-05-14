#include "Matrix2.h"

//all of the decimal types
template class Matrix2T<float>;
template class Matrix2T<double>;
template class Matrix2T<long double>;

//default constructor
TEMPLATE
Matrix2T<T>::Matrix2T()
{
	//create an empty matrix
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mat[i][j] = 0.0f;
		}
	}
}

//argument constructor
TEMPLATE
Matrix2T<T>::Matrix2T(T m11, T m12, T m21, T m22)
{
	//assign the arguments individually
	mat[0][0] = m11;
	mat[0][1] = m12;
	mat[1][0] = m21;
	mat[1][1] = m22;
}

//subscript operator
TEMPLATE
Vector2T<T> & Matrix2T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return mat[0];
	case 1: return mat[1];
	default: throw;
	}
}

//cast to T pointer overload
TEMPLATE
Matrix2T<T>::operator T*()
{
	return &mat[0][0];
}

//multiplication operator
TEMPLATE
Matrix2T<T> Matrix2T<T>::operator*(Matrix2T<T> other)
{
	Matrix2T<T> product = {};

	//a = Matrix2T that this function is running through
	//b = Matrix2T other passed into the function

	//iterate across a's rows
	for (int am = 0; am < 2; am++)
	{
		//iterate across b's columns
		for (int bn = 0; bn < 2; bn++)
		{
			//iterate across a's columns and b's rows
			for (int i = 0; i < 2; i++)
			{
				product[bn][am] = product[bn][am] + mat[i][am] * other.mat[bn][i];
			}
		}
	}

	return product;
}

//convert to identity matrix
TEMPLATE
void Matrix2T<T>::identity()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//checks if the iterators are on a diagonal
			mat[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

//rotation matrix
TEMPLATE
void Matrix2T<T>::setRotate(T radians)
{
	mat[0][0] = (T)cos(radians);
	mat[0][1] = (T)sin(radians);
	mat[1][0] = (T)-sin(radians);
	mat[1][1] = (T)cos(radians);
}

//transpose the matrix
TEMPLATE
void Matrix2T<T>::transpose()
{
	Matrix2T<T> temp = *this;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mat[j][i] = temp.mat[i][j];
		}
	}
}

//determinant from matrix
TEMPLATE
T Matrix2T<T>::determinant()
{
	/*
	* (what each letter represents in the matrix)
	* a b
	* c d
	*/

	T a = mat[0][0];
	T b = mat[0][1];
	T c = mat[1][0];
	T d = mat[1][1];

	return a * d - b * c;
}

//invert the matrix
TEMPLATE
bool Matrix2T<T>::invert()
{
	T determinant = this->determinant();

	//matrices can't be inverted 
	if (determinant == 0)
	{
		return false;
	}

	T a = mat[0][0];
	T b = mat[0][1];

	T c = mat[1][0];
	T d = mat[1][1];

	mat[0][0] = d / determinant;
	mat[0][1] = -b / determinant;

	mat[1][0] = -c / determinant;
	mat[1][1] = a / determinant;

	return true;
}
