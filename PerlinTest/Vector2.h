#pragma once
#include <math.h>

namespace MathLib
{
	class Vector2	//A mathamatical 2d vector
	{
	public:
		Vector2(float X = 0.f, float Y = 0.f);
		~Vector2();

		void operator+=(const Vector2& rhs);
		void operator-=(const Vector2& rhs);
		void operator*=(const float& scalar);
		void operator/=(const float& scalar);

		float Magnitude();

		float x, y;
	};

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
	Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

	float DotProduct(const Vector2 & lhs, const Vector2 & rhs);
}
