#include "Matrix4.h"
#include "Matrix3.h" //determinant process relies on matrix3

//all of the decimal types
template class Matrix4T<float>;
template class Matrix4T<double>;
template class Matrix4T<long double>;

TEMPLATE
//default constructor
Matrix4T<T>::Matrix4T()
{
	//create an empty matrix
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = 0.0f;
		}
	}
}

//argument constructor
TEMPLATE
Matrix4T<T>::Matrix4T(T m11, T m12, T m13, T m14, 
				 T m21, T m22, T m23, T m24,
				 T m31, T m32, T m33, T m34,
				 T m41, T m42, T m43, T m44)
{
	//assign the arguments individually
	mat[0][0] = m11;
	mat[0][1] = m12;
	mat[0][2] = m13;
	mat[0][3] = m14;

	mat[1][0] = m21;
	mat[1][1] = m22;
	mat[1][2] = m23;
	mat[1][3] = m24;

	mat[2][0] = m31;
	mat[2][1] = m32;
	mat[2][2] = m33;
	mat[2][3] = m34;

	mat[3][0] = m41;
	mat[3][1] = m42;
	mat[3][2] = m43;
	mat[3][3] = m44;
}

//subscript operator
TEMPLATE
Vector4T<T> & Matrix4T<T>::operator[](const int index)
{
	switch (index)
	{
	case 0: return mat[0];
	case 1: return mat[1];
	case 2: return mat[2];
	case 3: return mat[3];
	default: throw;
	}	
}

//cast to T pointer overload
TEMPLATE
Matrix4T<T>::operator T*()
{
	return &mat[0][0];
}


//multiplication operator
TEMPLATE
Matrix4T<T> Matrix4T<T>::operator*(Matrix4T<T> other)
{
	Matrix4T<T> product = {};

	//a = Matrix4T<T> that this function is running through
	//b = Matrix4T<T> other passed into the function

	//iterate across a's rows
	for (int am = 0; am < 4; am++)
	{
		//iterate across b's columns
		for (int bn = 0; bn < 4; bn++)
		{
			//iterate across a's columns and b's rows
			for (int i = 0; i < 4; i++)
			{
				product[bn][am] = product[bn][am] + mat[i][am] * other.mat[bn][i];
			}
		}
	}

	return product;
}

//convert to identity matrix
TEMPLATE
void Matrix4T<T>::identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//checks if the iterators are on a diagonal
			mat[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

//3D homogeneous rotation matrix around X (YZ affected)
TEMPLATE
void Matrix4T<T>::setRotateX(T radians)
{
	identity(); //all other elements are reset
	mat[1][1] = (T)cos(radians);
	mat[1][2] = (T)sin(radians);
	mat[2][1] = (T)-sin(radians);
	mat[2][2] = (T)cos(radians);
}

//3D homogeneous rotation matrix around Y (XZ affected)
TEMPLATE
void Matrix4T<T>::setRotateY(T radians)
{
	identity(); //all other elements are reset
	mat[0][0] = (T)cos(radians);
	mat[0][2] = (T)-sin(radians);
	mat[2][0] = (T)sin(radians);
	mat[2][2] = (T)cos(radians);
}

//3D homogeneous rotation matrix around Z (XY affected)
TEMPLATE
void Matrix4T<T>::setRotateZ(T radians)
{
	identity(); //all other elements are reset
	mat[0][0] = (T)cos(radians);
	mat[0][1] = (T)sin(radians);
	mat[1][0] = (T)-sin(radians);
	mat[1][1] = (T)cos(radians);
}

//transpose matrix
TEMPLATE
void Matrix4T<T>::transpose()
{
	Matrix4T<T> temp = *this;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j][i] = temp.mat[i][j];
		}
	}
}


//determinant from matrix
TEMPLATE
T Matrix4T<T>::determinant()
{
	/*
	* (what each letter represents in the matrix)
	* a b c d
	* e f g h
	* i j k l
	* m n o p
	*/

	T a = mat[0][0];
	T b = mat[0][1];
	T c = mat[0][2];
	T d = mat[0][3];

	T e = mat[1][0];
	T f = mat[1][1];
	T g = mat[1][2];
	T h = mat[1][3];

	T i = mat[2][0];
	T j = mat[2][1];
	T k = mat[2][2];
	T l = mat[2][3];

	T m = mat[3][0];
	T n = mat[3][1];
	T o = mat[3][2];
	T p = mat[3][3];

	Matrix3T<T> m1 = Matrix3T<T>{ f,g,h,j,k,l,n,o,p };
	Matrix3T<T> m2 = Matrix3T<T>{ e,g,h,i,k,l,m,o,p };
	Matrix3T<T> m3 = Matrix3T<T>{ e,f,h,i,j,l,m,n,p };
	Matrix3T<T> m4 = Matrix3T<T>{ e,f,g,i,j,k,m,n,o };

	return a * m1.determinant() - b * m2.determinant() + c * m3.determinant() - d * m4.determinant();
}

//invert the matrix
TEMPLATE
bool Matrix4T<T>::invert()
{
	T determinant = this->determinant();

	//if the determinant is 0, the inversion wont work
	if (determinant == 0)
	{
		return false;
	}

	T invDet = 1 / determinant;

	Matrix3T<T> detMats[16];

	//make sub-matrices
	for (int i = 0; i < 16; i++)
	{
		int count = 0;

		for (int m = 0; m < 4; m++)
		{
			for (int n = 0; n < 4; n++)
			{
				int cm = i / 4;
				int cn = i % 4;

				if (cm != m && cn != n)
				{
					detMats[i].mat[count / 3][count % 3] = mat[m][n];
					count++;
				}
			}
		}
	}

	//set the matrix to be determinants of the sub-matrix
	for (int i = 0; i < 16; i++)
	{
		int cm = i / 4;
		int cn = i % 4;

		mat[cm][cn] = detMats[i].determinant();
	}

	//transpose the matrix
	transpose();

	//negate every odd element 1,3,5,7..., 
	for (int i = 0; i < 16; i++)
	{
		int cm = i / 4;
		int cn = i % 4;

		//switching between odd and even calculations
		if (i % 2 == 1 - cm % 2)
		{
			mat[cm][cn] *= -1;
		}
	}


	//divide by the determinant
	for (int i = 0; i < 16; i++)
	{
		int cm = i / 4;
		int cn = i % 4;

		//divide by the determinant of the 4x4
		mat[cm][cn] *= invDet;
	}

	return true;
}

//3D scale matrix
TEMPLATE
void Matrix4T<T>::setScale(Vector3T<T> scale)
{
	identity(); //all other elements are reset

	mat[0][0] = scale.x;
	mat[1][1] = scale.y;
	mat[2][2] = scale.z;
}

//3D translation matrix
TEMPLATE
void Matrix4T<T>::setTranslate(Vector3T<T> translate)
{
	identity(); //all other elements are reset

	mat[3][0] = translate.x;
	mat[3][1] = translate.y;
	mat[3][2] = translate.z;
}

//applies a relative translation to a matrix
TEMPLATE
void Matrix4T<T>::translate(Vector3T<T> translate)
{
	mat[3][0] += translate.x;
	mat[3][1] += translate.y;
	mat[3][2] += translate.z;
}

//applies a relative scale to a matrix
TEMPLATE
void Matrix4T<T>::scale(Vector3T<T> scale)
{
	mat[0][0] *= scale.x;
	mat[0][1] *= scale.x;
	mat[0][2] *= scale.x;

	mat[1][0] *= scale.y;
	mat[1][1] *= scale.y;
	mat[1][2] *= scale.y;

	mat[2][0] *= scale.z;
	mat[2][1] *= scale.z;
	mat[2][2] *= scale.z;
}

//get scale from 4D matrix
TEMPLATE
Vector3T<T> Matrix4T<T>::getScale()
{
	//get the sign of the scale x
	T signX = mat[0][0] > 0 ? (T)1 : (T)-1;
	signX = mat[0][0] == 0 ? (T)0 : signX;

	//get the sign of the scale y
	T signY = mat[1][1] > 0 ? (T)1 : (T)-1;
	signY = mat[1][1] == 0 ? (T)0 : signY;

	//get the sign of the scale y
	T signZ = mat[2][2] > 0 ? (T)1 : (T)-1;
	signZ = mat[2][2] == 0 ? (T)0 : signZ;

	//scale decomposition
	T sX = signX * (T)sqrt(mat[0][0] * mat[0][0] + mat[0][1] * mat[0][1] + mat[0][2] * mat[0][2]);
	T sY = signY * (T)sqrt(mat[1][0] * mat[1][0] + mat[1][1] * mat[1][1] + mat[1][2] * mat[1][2]);
	T sZ = signZ * (T)sqrt(mat[2][0] * mat[2][0] + mat[2][1] * mat[2][1] + mat[2][2] * mat[2][2]);

	return Vector3T<T>{sX, sY, sZ};
}

//applies a relative rotation (YZ affected) to a matrix
TEMPLATE
void Matrix4T<T>::rotateX(T radians)
{
	Matrix4T<T> other;
	other.setRotateX(radians);

	*this = other * *this;
}

//applies a relative rotation (XZ affected) to a matrix
TEMPLATE
void Matrix4T<T>::rotateY(T radians)
{
	Matrix4T<T> other;
	other.setRotateY(radians);

	*this = other * *this;
}


//applies a relative rotation (XY affected) to a matrix
TEMPLATE
void Matrix4T<T>::rotateZ(T radians)
{
	Matrix4T<T> other;
	other.setRotateZ(radians);

	*this = other * *this;
}

//rotates by Z, then Y, then X
TEMPLATE
void Matrix4T<T>::rotateEuler(Vector3T<T> angles)
{
	Matrix4T<T> X;
	Matrix4T<T> Y;
	Matrix4T<T> Z;

	//individual rotations
	X.setRotateX(angles.x);
	Y.setRotateY(angles.y);
	Z.setRotateZ(angles.z);

	*this = X * Y * Z * *this;
}


//get the rotation around the X axis
TEMPLATE
T Matrix4T<T>::getRotationX()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix4T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T roll = 0;

	if (copy.mat[0][0] != 1 && copy.mat[0][0] != -1)
	{
		T roll = (T)atan2(-copy.mat[1][2], copy.mat[1][1]);
	}

	return roll;
}

//get the rotation around the Y axis
TEMPLATE
T Matrix4T<T>::getRotationY()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix4T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T pitch = 0;

	if (copy.mat[0][0] == 1 || copy.mat[0][0] == -1)
	{
		T pitch = (T)atan2(copy.mat[0][2], copy.mat[2][3]);
	}
	else
	{
		T pitch = (T)atan2(-copy.mat[2][0], copy.mat[0][0]);
	}

	return pitch;
}

//get the rotation around the Z axis
TEMPLATE
T Matrix4T<T>::getRotationZ()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix4T<T> copy = *this;
	copy.scale(scaleVec); //normalise the matrix copy by applying an inverse scale

	T yaw = 0;

	if (copy.mat[0][0] != 1 && copy.mat[0][0] != -1)
	{
		T yaw = (T)asin(copy.mat[1][0]);
	}

	return yaw;
}

//gets all rotation as euler angles
TEMPLATE
Vector3T<T> Matrix4T<T>::getEuler()
{
	Vector3T<T> scaleVec = getScale();
	scaleVec = 1 / scaleVec;

	Matrix4T<T> copy = *this;
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

//generate an orientation that makes an observer at one point face another point
TEMPLATE
void Matrix4T<T>::lookAt(Vector3T<T> eye, Vector3T<T> target, Vector3T<T> up)
{

	Vector3T<T> zAxis = (target - eye).normalised();
	Vector3T<T> xAxis = (up * -1).cross(zAxis).normalised();
	Vector3T<T> yAxis = zAxis.cross(xAxis);

	Matrix4T<T> look;

	T xDot = -xAxis.dot(eye);
	T yDot = -yAxis.dot(eye);
	T zDot = -zAxis.dot(eye);

	look.identity();

	look[0][0] = xAxis.x;
	look[0][1] = xAxis.y;
	look[0][2] = xAxis.z;

	look[1][0] = yAxis.x;
	look[1][2] = yAxis.y;
	look[1][2] = yAxis.z;

	look[2][0] = zAxis.x;
	look[2][1] = zAxis.y;
	look[2][2] = zAxis.z;

	look[0][3] = xDot;
	look[1][3] = yDot;
	look[2][3] = zDot;

	*this = look;
}

//3D camera transformation
TEMPLATE
void Matrix4T<T>::generateProjection(T fovX, T fovY, T zNear, T zFar)
{
	Matrix4T<T> projection = Matrix4T<T>{};

	projection[0][0] = (T)atan(fovX / 2);
	projection[1][1] = (T)atan(fovY / 2);
	projection[2][2] = -(zFar + zNear) / (zFar - zNear);
	projection[3][2] = -(2 * zNear * zFar) / (zFar - zNear);
	projection[2][3] = -1;
	projection[3][3] = 0;

	*this = projection;
}
