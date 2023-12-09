#pragma once
#ifndef PHYSICS_RIGIDBODY_CONTACT_H
#define PHYSICS_RIGIDBODY_CONTACT_H

#include "../../BaseClasses/Vector2D.h"
#include "Rigidbody2D.h"

namespace physics
{
	class RigidbodyContact
	{
	public:
		Rigidbody2D* body[2];
		Vector2D contactPoint;
		Vector2D contactNormal;
		float restitution;
		float penetration;

		Vector2D relativeContactPosition[2];
		Vector2D contactVelocity;
		float impulseMagnitude;

		void CalculateInternals(float deltaTime);
		Vector2D CalculateLocalVelocity(unsigned bodyIndex, float deltaTime);
		void ApplyImpulse();
	};

	class RigidbodyContactResolver
	{
	public:
		void ResolveContacts(RigidbodyContact* contactArray, unsigned numContact, float deltaTime);
	};

}


#endif


