#pragma once
#ifndef PHYSICS_PARTICLE_OVERLAP_CONTACT
#define PHYSICS_PARTICLE_OVERLAP_CONTACT

#include <vector>

#include "ParticleContactGenerator.h"


namespace physics
{
	class ParticleOverlapContact :	public ParticleContactGenerator
	{
	public:
		ParticleOverlapContact(float restitution);

		void AddParticle(Particle3D* particle);
		unsigned FillContact(ParticleContact* contact, unsigned limit) override;

		std::vector<Particle3D*> particleList;
		float restitution;
	};
}
#endif


