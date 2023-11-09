#pragma once
#ifndef PHYSICS_PARTICLE_GROUND_CONTACT_H
#define PHYSICS_PARTICLE_GROUND_CONTACT_H

#include <vector>
#include "ParticleContactGenerator.h"

namespace physics
{
	class ParticleGroundContact :  public ParticleContactGenerator
	{
	public:
		ParticleGroundContact(float yLimit, float restitution);

		void AddParticle(Particle3D* particle);
		virtual unsigned FillContact(ParticleContact* contact, unsigned limit);

		std::vector<Particle3D*> particleList;
		float yLimit;
		float restitution;
	};
}


#endif

