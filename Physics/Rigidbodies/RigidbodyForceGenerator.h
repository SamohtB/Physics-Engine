#pragma once
#ifndef PHYSICS_RIGIDBODY_FORCE_GENERATOR_H
#define PHYSICS_RIGIDBODY_FORCE_GENERATOR_H

#include "Rigidbody2D.h"

namespace physics
{
	class RigidbodyForceGenerator
	{
	public:
		virtual void UpdateForce(Rigidbody2D* rigidbody, float duration) = 0;
	};

	class RigidbodyForceRegistry
	{
	protected:
		struct RigidbodyForceRegistration
		{
			Rigidbody2D* rigidbody;
			RigidbodyForceGenerator* forceGenerator;
		};

		typedef std::vector<RigidbodyForceRegistration> Registry;
		Registry registrations;

	public:
		void Add(Rigidbody2D* rigidbody, RigidbodyForceGenerator* forceGenerator);
		//void Remove(Rigidbody2D* rigidbody, RigidbodyForceGenerator* forceGenerator);
		//void Clear();
		void UpdateForces(float duration);


	};

}

#endif