#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <math.h>
#include <iostream>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

template <typename T> int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

struct Vector2 
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSqr()
	{
		return x*x + y*y;
	}

	float Magnitude()
	{
		return (float)sqrt(x*x + y*y);
	}

	Vector2 Normalize()
	{
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2 Invert()
	{
		return Vector2(y, x);
	}

	Vector2& operator +=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2& operator *=(const float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2 operator -() const
	{
		return Vector2(-x, -y);
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 operator *(const float& lhs, const Vector2& rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

inline Vector2 operator /(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
}

inline Vector2 operator /(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}

inline Vector2 operator /(const float& lhs, const Vector2& rhs)
{
	return Vector2(lhs / rhs.x, lhs / rhs.y);
}

inline Vector2 RotateVector(const Vector2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2(((float)vec.x * cos(radAngle) - vec.y * sin(radAngle)), ((float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))));
}

inline float Dot(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value > max)
		return max;
	else if (value < min)
		return min;
	
	return value;
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, -1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };

#endif