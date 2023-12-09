#pragma once
#ifndef PHYSICS_SHAPE_2D_H
#define PHYSICS_SHAPE_2D_H

namespace physics
{
	class Shape2D
	{
	public:
		virtual float GetInertiaTensor(float mass) = 0;
	};

	class RectShape2D : public Shape2D
	{
		public:
		RectShape2D(float width = 0.0f, float height = 0.0f) : width(width), height(height) {}
		float GetInertiaTensor(float mass) override;

	private:
		float width;
		float height;
	};

	class CircleShape2D : public Shape2D
	{
	public:
		CircleShape2D(float radius) : radius(radius) {}
		float GetInertiaTensor(float mass) override;

	private:
		float radius;
		
	};
}


#endif

