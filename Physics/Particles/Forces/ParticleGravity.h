#pragma once
#ifndef PHYSICS_PARTICLES_GRAVITY_H
#define PHYSICS_PARTICLES_GRAVITY_H

#include "IParticleForceGenerator.h"

namespace physics
{
	class ParticleGravity : public IParticleForceGenerator
	{
	public:
		ParticleGravity(Vector3D gravity) : gravity(gravity) {}
		
		void UpdateForce(Particle3D* particle, float duration) override;
	private:
		Vector3D gravity;
	};
}

#endif // PHYSICS_PARTICLES_GRAVITY_H



