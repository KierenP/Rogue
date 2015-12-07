#include "Vector3.h"


namespace MathLib
{
	Vector3::Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	Vector3::~Vector3()
	{
	}

	void Vector3::operator+=(const Vector3 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	void Vector3::operator-=(const Vector3 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	void Vector3::operator*=(const float & scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void Vector3::operator/=(const float & scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

	float Vector3::Magnitude()
	{
		return static_cast<float>(sqrt(x*x + y*y + z*z));
	}

	Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	Vector3 operator*(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	Vector3 operator/(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	Vector3 CrossProduct(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x);
	}

	float DotProduct(const Vector3 & lhs, const Vector3 & rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
}
