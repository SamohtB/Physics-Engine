#pragma once
#ifndef PHYSICS_RIGIDBODY_SPRING_H
#define PHYSICS_RIGIDBODY_SPRING_H

#include "RigidbodyForceGenerator.h"

namespace physics
{
	class RigidbodySpring : public RigidbodyForceGenerator
	{
		Vector2D localConnection;
		Rigidbody2D* other;
		Vector2D otherLocalConnection;
		float springConstant;
		float restLength;

	public:
		RigidbodySpring(Vector2D localConnection, Rigidbody2D* other, Vector2D otherLocalConnection, float springConstant, float restLenght) :
		localConnection(localConnection), other(other), otherLocalConnection(otherLocalConnection), springConstant(springConstant), restLength(restLenght) {}

		virtual void UpdateForce(Rigidbody2D* rigidbody, float duration) override;
	};
}


#endif


