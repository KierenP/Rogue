#pragma once
#include <math.h>

namespace MathLib
{
	class Vector3	//A mathamatical 3d vector
	{
	public:
		Vector3(float X = 0.f, float Y = 0.f, float Z = 0.f);
		~Vector3();

		void operator+=(const Vector3& rhs);
		void operator-=(const Vector3& rhs);
		void operator*=(const float& scalar);
		void operator/=(const float& scalar);

		float Magnitude();

		float x, y, z;
	};

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
	Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

	Vector3 CrossProduct(const Vector3 & lhs, const Vector3 & rhs);	
	float DotProduct(const Vector3 & lhs, const Vector3 & rhs);
}

