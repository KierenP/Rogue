#include "Vector2.h"

namespace MathLib
{
	Vector2::Vector2(float X, float Y)
	{
		x = X;
		y = Y;
	}

	Vector2::~Vector2()
	{
	}

	void Vector2::operator+=(const Vector2 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	void Vector2::operator-=(const Vector2 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}

	void Vector2::operator*=(const float & scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	void Vector2::operator/=(const float & scalar)
	{
		x /= scalar;
		y /= scalar;
	}

	float Vector2::Magnitude()
	{
		return sqrt(x*x + y*y);
	}

	Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2 operator*(const Vector2 & lhs, const Vector2 & rhs)
	{
		return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	Vector2 operator/(const Vector2 & lhs, const Vector2 & rhs)
	{
		return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	float DotProduct(const Vector2 & lhs, const Vector2 & rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
}