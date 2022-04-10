#pragma once

struct Vector3
{
public:
	Vector3()  = default;
	Vector3(float x, float y, float z) ;

	Vector3 operator+(const Vector3&) ;
	Vector3 operator-(const Vector3&) ;
	Vector3 operator*(const Vector3&) ;
	Vector3 operator*(const float) ;

	inline float sqrMagnitude() const ;
	inline float magnitude() const ;

	float x = 0;
	float y = 0;
	float z = 0;
};

