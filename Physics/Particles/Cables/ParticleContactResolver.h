#pragma once
#ifndef PHYSICS_PARTICLE_CONTACT_RESOLVER
#define PHYSICS_PARTICLE_CONTACT_RESOLVER

#include "ParticleContact.h"

namespace physics
{
	class ParticleContactResolver
	{
	protected:
		unsigned iterations;
	public:
		ParticleContactResolver(unsigned iterations);
		void SetIterations(unsigned iterations);
		void ResolveContacts(ParticleContact *contactArray, unsigned numContacts, float duration);
	};
}

#endif // !PHYSICS_PARTICLE_CONTACT_RESOLVER



