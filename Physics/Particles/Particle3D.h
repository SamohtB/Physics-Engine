#pragma once
#ifndef PHYSICS_PARTICLES2D_H
#define PHYSICS_PARTICLES2D_H

#include "../../BaseClasses/Vector3D.h"
#include <cassert>

namespace physics
{
	using namespace baseclass;
	class Particle3D
	{
	public:
		Particle3D();
		void Integrate(float deltaTime);

		void SetDamping(float damping);
		float GetDamping();

		void SetMass(float mass);
		float GetMass();
		float GetInverseMass();

		void SetVelocity(Vector3D velocity);
		Vector3D GetVelocity();

		void SetAcceleration(Vector3D acceleration);
		Vector3D GetAcceleration();

		void SetPosition(Vector3D position);
		Vector3D GetPosition();
		Vector3D* GetPositionReference();

		void AddForce(Vector3D force);
		void ClearAccumulator();

		void SetRadius(float radius);
		float GetRadius();

	private:
		float mass;
		float inverseMass;
		float damping;
		float radius;

		Vector3D position;
		Vector3D velocity;
		Vector3D acceleration;
		Vector3D forceAccumulator;
	};
}
#endif // !PHYSICS_PARTICLES2D_H
