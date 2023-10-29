#pragma once
#ifndef PHYSICS_PARTICLE_DRAG_H
#define PHYSICS_PARTICLE_DRAG_H

#include "IParticleForceGenerator.h"

namespace physics
{
	class ParticleDrag : public IParticleForceGenerator
	{
	public:
		ParticleDrag(float k1, float k2) : k1(k1), k2(k2) {}

		virtual void UpdateForce(Particle3D* particle, float deltaTime);
	private:
		float k1;
		float k2;
	};
}
#endif // !PHYSICS_PARTICLE_DRAG_H



