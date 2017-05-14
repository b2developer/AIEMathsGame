#include "Matrix3.h"
#include "Vector2.h"

//all of the decimal types
template class Matrix3T<float>;
template class Matrix3T<double>;
template class Matrix3T<long double>;

//default constructor
TEMPLATE
Matrix3T<T>::Matrix3T()
{
	//create an empty matrix
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = 0.0f;
		}
	}
}

//argument constructor
TEMPLATE
Matrix3T<T>::Matrix3T(T m11, T m12, T m13, 
				 T m21, T m22, T m23, 
				 T m31, T m32, T m33)
{
	//assign the arguments individually
	mat[0][0] = m11;
	mat[0][1] = m12;
	mat[0][2] = m13;

	mat[1][0] = m21;
	mat[1][1] = m22;
	mat[1][2] = m23;

	mat[2][0] = m31;
	mat[2][1] = m32;
	mat[2][2] = m33;
}


//subscript operator
TEMPLATE
Vector3T<T> & Matrix3T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return mat[0];
	case 1: return mat[1];
	case 2: return mat[2];
	default: throw;
	}
}

//cast to T pointer overload
TEMPLATE
Matrix3T<T>::operator T*()
{
	return &mat[0][0];
}

//multiplication operator
TEMPLATE
Matrix3T<T> Matrix3T<T>::operator*(Matrix3T<T> other)
{
	Matrix3T<T> product = {};

	//a = Matrix3T<T> that this function is running through
	//b = Matrix3T<T> other passed into the function

	//iterate across a's rows
	for (int am = 0; am < 3; am++)
	{
		//iterate across b's columns
		for (int bn = 0; bn < 3; bn++)
		{
			//iterate across a's columns and b's rows
			for (int i = 0; i < 3; i++)
			{
				product[bn][am] = product[bn][am] + mat[i][am] * other.mat[bn][i];
			}
		}
	}

	return product;
}

//convert to identity matrix
TEMPLATE
void Matrix3T<T>::identity()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//checks if the iterators are on a diagonal
			mat[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

//3D rotation matrix around X (YZ affected)
TEMPLATE
void Matrix3T<T>::setRotateX(T radians)
{
	identity(); //all other elements are reset
	mat[1][1] = (T)cos(radians);
	mat[1][2] = (T)sin(radians);
	mat[2][1] = (T)-sin(radians);
	mat[2][2] = (T)cos(radians);
}

//3D rotation matrix around Y (XZ affected)
TEMPLATE
void Matrix3T<T>::setRotateY(T radians)
{
	identity(); //all other elements are reset
	mat[0][0] = (T)cos(radians);
	mat[0][2] = (T)-sin(radians);
	mat[2][0] = (T)sin(radians);
	mat[2][2] = (T)cos(radians);
}

//3D rotation matrix around Z (XY affected)
TEMPLATE
void Matrix3T<T>::setRotateZ(T radians)
{
	identity(); //all other elements are reset
	mat[0][0] = (T)cos(radians);
	mat[0][1] = (T)sin(radians);
	mat[1][0] = (T)-sin(radians);
	mat[1][1] = (T)cos(radians);
}

//transpose matrix
TEMPLATE
void Matrix3T<T>::transpose()
{
	Matrix3T<T> temp = *this;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mat[j][i] = temp.mat[i][j];
		}
	}
}

//determinant from matrix
TEMPLATE
T Matrix3T<T>::determinant()
{
	/*
	* (what each letter represents in the matrix)
	* a b c
	* d e f
	* g h i
	*/

	T a = mat[0][0];
	T b = mat[0][1];
	T c = mat[0][2];

	T d = mat[1][0];
	T e = mat[1][1];
	T f = mat[1][2];

	T g = mat[2][0];
	T h = mat[2][1];
	T i = mat[2][2];

	//combining the variables
	T aei = a * i * e; 
	T bfg = b * f * g;
	T cdh = c * d * h;
	T ceg = c * e * g;
	T bdi = b * d * i;
	T afh = a * f * h;

	return aei + bfg + cdh - ceg - bdi - afh;
}

//invert the matrix
TEMPLATE
bool Matrix3T<T>::invert()
{
	T determinant = this->determinant();

	//matrices can't be inverted 
	if (determinant == 0)
	{
		return false;
	}

	T a = mat[0][0];
	T b = mat[0][1];
	T c = mat[0][2];
	T d = mat[1][0];
	T e = mat[1][1];
	T f = mat[1][2];
	T g = mat[2][0];
	T h = mat[2][1];
	T i = mat[2][2];

	//this is done to make the final inversion step lest clustered
	T A = (e * i - f * h);
	T B = -(d * i - f * g);
	T C = (d * h - e * g);
	T D = -(b * i - c * h);
	T E = (a * i - c * g);
	T F = -(a * h - b * g);
	T G = (b * f - c * e);
	T H = -(a * f - c * d);
	T I = (a * e - b * d);

	mat[0][0] = A / determinant;
	mat[0][1] = D / determinant;
	mat[0][2] = G / determinant;

	mat[1][0] = B / determinant;
	mat[1][1] = E / determinant;
	mat[1][2] = H / determinant;

	mat[2][0] = C / determinant;
	mat[2][1] = F / determinant;
	mat[2][2] = I / determinant;

	return true;
}

//2D scale matrix
TEMPLATE
void Matrix3T<T>::setScale(Vector2T<T> scale)
{
	identity(); //all other elements are reset

	mat[0][0] = scale.x;
	mat[1][1] = scale.y;
}

//2D translation matrix
TEMPLATE
void Matrix3T<T>::setTranslate(Vector2T<T> translate)
{
	identity(); //all other elements are reset

	mat[2][0] = translate.x;
	mat[2][1] = translate.y;
}

//applies a relative translation to a matrix
TEMPLATE
void Matrix3T<T>::translate(Vector2T<T> translate)
{
	mat[2][0] += translate.x;
	mat[2][1] += translate.y;
}

//applies a relative scale to a matrix
TEMPLATE
void Matrix3T<T>::scale(Vector2T<T> scale)
{
	mat[0][0] *= scale.x;
	mat[0][1] *= scale.x;

	mat[1][0] *= scale.y;
	mat[1][1] *= scale.y;
}

//applies a relative rotation (YZ affected) to a matrix
TEMPLATE
void Matrix3T<T>::rotateX(T radians)
{
	Matrix3T<T> other;
	other.setRotateX(radians);

	*this = other * *this;
}

//applies a relative rotation (XZ affected) to a matrix
TEMPLATE
void Matrix3T<T>::rotateY(T radians)
{
	Matrix3T<T> other;
	other.setRotateY(radians);

	*this = other * *this;
}


//applies a relative rotation (XY affected) to a matrix
TEMPLATE
void Matrix3T<T>::rotateZ(T radians)
{
	Matrix3T<T> other;
	other.setRotateZ(radians);

	*this = other * *this;
}

//rotates by Z, then Y, then X
TEMPLATE 
void Matrix3T<T>::rotateEuler(Vector3T<T> angles)
{
	Matrix3T<T> X;
	Matrix3T<T> Y;
	Matrix3T<T> Z;

	//individual rotations
	X.setRotateX(angles.x);
	Y.setRotateY(angles.y);
	Z.setRotateZ(angles.z);

	*this = X * Y * Z * *this;
}

//get scale from 3D matrix
TEMPLATE
Vector2T<T> Matrix3T<T>::getScale()
{
	//get the sign of the scale x
	T signX = mat[0][0] > 0 ? (T)1 : (T)-1;
	signX = mat[0][0] == 0 ? (T)0 : signX;

	//get the sign of the scale y
	T signY = mat[1][1] > 0 ? (T)1 : (T)-1;
	signY = mat[1][1] == 0 ? (T)0 : signY;

	//scale decomposition
	T sX = signX * (T)sqrt(mat[0][0] * mat[0][0] + mat[0][1] * mat[0][1]);
	T sY = signY * (T)sqrt(mat[1][0] * mat[1][0] + mat[1][1] * mat[1][1]);

	return Vector2T<T>{sX, sY};
}

//gets the rotation along the x axis from 3D matrix (decomposition of a 2D transformation matrix)
TEMPLATE
T Matrix3T<T>::getRotation()
{
	return (T)atan2(-mat[0][1], mat[0][0]);
}

//get the rotation around the X axis (decomposition of a 3D rotation matrix)
TEMPLATE
T Matrix3T<T>::getRotationX()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix3T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T roll = 0;

	if (copy.mat[0][0] != 1 || copy.mat[0][0] != -1)
	{
		roll = (T)atan2(-copy.mat[1][2], copy.mat[1][1]);
	}

	return roll;
}

//get the rotation around the Y axis (decomposition of a 3D rotation matrix)
TEMPLATE
T Matrix3T<T>::getRotationY()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix3T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T pitch = 0;

	if (copy.mat[0][0] == 1 || copy.mat[0][0] == -1)
	{
		pitch = (T)atan2(copy.mat[0][2], copy.mat[2][3]);
	}
	else
	{
		pitch = (T)atan2(-copy.mat[2][0], copy.mat[0][0]);
	}

	return pitch;
}

//get the rotation around the Z axis
TEMPLATE
T Matrix3T<T>::getRotationZ()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix3T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T yaw = 0;

	if (copy.mat[0][0] != 1 || copy.mat[0][0] != -1)
	{
		yaw = (T)asin(copy.mat[1][0]);
	}

	return yaw;
}

//gets all rotation as euler angles (decomposition of a 3D rotation matrix)
TEMPLATE
Vector3T<T> Matrix3T<T>::getEuler()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix3T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	if (copy.mat[0][0] == 1 || copy.mat[0][0] == -1)
	{
		T pitch = (T)atan2(copy.mat[0][2], copy.mat[2][3]);
		return Vector3T<T>{0, pitch, 0};
	}
	else
	{
		T yaw = (T)asin(copy.mat[0][1]);
		T pitch = (T)atan2(-copy.mat[0][2], copy.mat[0][0]);
		T roll = (T)atan2(-copy.mat[2][1], copy.mat[1][1]);

		return Vector3T<T>{roll, pitch, yaw};
	}
}

//rotation matrix from directional vector
TEMPLATE
void Matrix3T<T>::lookAt(Vector3T<T> direction, Vector3T<T> up)
{
	Vector3T<T> zAxis = direction.normalised();
	Vector3T<T> xAxis = (up * -1).cross(zAxis).normalised();
	Vector3T<T> yAxis = zAxis.cross(xAxis);

	Matrix3T<T> look;

	look.identity();

	look[0][0] = xAxis.x;
	look[0][1] = xAxis.y;
	look[0][2] = xAxis.z;

	look[1][0] = yAxis.x;
	look[1][1] = yAxis.y;
	look[1][2] = yAxis.z;

	look[2][0] = zAxis.x;
	look[2][1] = zAxis.y;
	look[2][2] = zAxis.z;

	*this = look;
}

