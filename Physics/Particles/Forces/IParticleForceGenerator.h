#pragma once
#ifndef PHYSICS_FORCE_GENERATOR_H
#define PHYSICS_FORCE_GENERATOR_H

#include "../Particle3D.h"

namespace physics
{
	class IParticleForceGenerator
	{
	public:
		virtual void UpdateForce(Particle3D* particle, float duration) = 0;
		virtual ~IParticleForceGenerator() = default;
	};
}

#endif