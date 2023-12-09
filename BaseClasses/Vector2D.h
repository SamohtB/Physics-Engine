#pragma once
#ifndef BASECLASS_VECTOR_2D_H
#define BASECLASS_VECTOR_2D_H

#include <iostream>

namespace baseclass
{
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Vector2D& other); 
		~Vector2D() = default;
		Vector2D& operator=(const Vector2D& other);
		Vector2D(Vector2D&& other) noexcept;
		Vector2D& operator=(Vector2D&& other) noexcept;

		Vector2D operator+(Vector2D vectorB) const;
		Vector2D operator+=(Vector2D vectorB);
		Vector2D operator-(Vector2D vectorB) const;
		Vector2D operator-=(Vector2D vectorB);
		Vector2D operator*(float scalar) const;
		Vector2D operator*=(float scalar);
		bool operator!=(Vector2D vectorB) const;
		bool operator==(Vector2D vectorB) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector);

		void Zero();

		float Dot(Vector2D vectorB);
		float Cross(const Vector2D &rhs);
		Vector2D Normalize();
		float GetMagnitude();
		float SquareMagnitude();

	public:
		float x;
		float y;

	private:
		float epsilon = 0.0001f;
	};
}

#endif



