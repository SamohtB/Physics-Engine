#pragma once
#ifndef PHYSICS_RIGIDBODY_GRAVITY_H
#define PHYSICS_RIGIDBODY_GRAVITY_H

#include "RigidbodyForceGenerator.h"

namespace physics
{
	class RigidbodyGravity : public RigidbodyForceGenerator
	{
		Vector2D gravity;

	public:
		RigidbodyGravity(Vector2D gravity) : gravity(gravity){};
		void UpdateForce(Rigidbody2D* rigidbody, float duration) override;
	};
}
#endif

