#pragma once
#ifndef PHYSICS_PARTICLE_WORLD_H
#define PHYSICS_PARTICLE_WORLD_H

#include <vector>

#include "Forces/ParticleForceRegistry.h"
#include "Cables/ParticleContactResolver.h"
#include "Cables/ParticleContactGenerator.h"

namespace  physics
{
	class ParticleWorld
	{
	public:
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0);
		~ParticleWorld();

		unsigned GenerateContacts();
		void StartFrame();

		void Integrate(float deltaTime);
		void RunPhysics(float deltaTime);

		unsigned maxContacts;
		bool calculateIterations;

		std::vector<Particle3D*> particleList;
		ParticleForceRegistry registry;

		ParticleContactResolver resolver;
		std::vector<ParticleContactGenerator*> particleContactGeneratorList;
		ParticleContact* particleContactArray;


	};
}

#endif


