#pragma once
#ifndef PHYSICS_PARTICLES2D_H
#define PHYSICS_PARTICLES2D_H

#include "../../BaseClasses/Vector2D.h"
#include <cassert>

namespace physics
{
	using namespace baseclass;
	class Particle2D
	{
	public:
		Particle2D();
		virtual void Integrate(float deltaTime);

		void SetDamping(float damping);
		float GetDamping();

		void SetMass(float mass);
		float GetMass();
		float GetInverseMass();

		void SetVelocity(Vector2D velocity);
		Vector2D GetVelocity();

		void SetAcceleration(Vector2D acceleration);
		Vector2D GetAcceleration();

		void SetPosition(Vector2D position);
		Vector2D GetPosition();
		Vector2D* GetPositionReference();

		void AddForce(Vector2D force);
		void ClearAccumulator();

		void SetRadius(float radius);
		float GetRadius();

	private:
		float mass;
		float inverseMass;
		float damping;
		float radius;

		Vector2D position;
		Vector2D velocity;
		Vector2D acceleration;

	public:
		Vector2D forceAccumulator;
	};
}
#endif // !PHYSICS_PARTICLES2D_H
