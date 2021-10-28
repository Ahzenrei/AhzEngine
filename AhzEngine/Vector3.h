#pragma once

struct Vector3
{
public:
	Vector3() noexcept = default;
	Vector3(float x, float y, float z) noexcept;

	Vector3 operator+(const Vector3&) noexcept;
	Vector3 operator-(const Vector3&) noexcept;
	Vector3 operator*(const Vector3&) noexcept;
	Vector3 operator*(const float) noexcept;

	inline float sqrMagnitude() const noexcept;
	inline float magnitude() const noexcept;

	float x = 0;
	float y = 0;
	float z = 0;
};

