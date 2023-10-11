#pragma once
#ifndef PHYSICS_PARTICLE_PHYSICS_REGISTRY_H
#define PHYSICS_PARTICLE_PHYSICS_REGISTRY_H

#include <vector>

#include "Particle3D.h"
#include "IParticleForceGenerator.h"

namespace physics
{
	class ParticleForceRegistry
	{
	protected:
		struct ParticleForceRegistration
		{
			Particle3D* particle;
			IParticleForceGenerator* forceGenerator;
		};

		typedef std::vector<ParticleForceRegistration> Registry;
		Registry registrations;

	public:
		void Add(Particle3D* particle, IParticleForceGenerator* forceGenerator);
		void Remove(Particle3D* particle, IParticleForceGenerator* forceGenerator);
		void Clear();
		void UpdateForces(float duration);
	};
}

#endif // !1






