#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float _x, float _y, float _z) 
	: x(_x), y(_y), z(_z)
{}

Vector3 Vector3::operator+(const Vector3& v) 
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) 
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const Vector3& v) 
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*(const float f) 
{
	return Vector3(x * f, y * f, z * f);
}

float Vector3::sqrMagnitude() const 
{
	return x*x + y*y + z*z;
}

float Vector3::magnitude() const 
{
	return sqrtf(sqrMagnitude());
}
