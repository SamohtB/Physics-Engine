#pragma once
#ifndef GAMECORE_MASS_AGGREGATE_SYSTEM
#define GAMECORE_MASS_AGGREGATE_SYSTEM

#include "../Physics/Particles/ParticleWorld.h"
#include "../Physics/Particles/Forces/ParticleGravity.h"

namespace gamecore
{
	using namespace physics;

	class MassAggregateSystem
	{
	public:
		MassAggregateSystem(Vector3D gravity = Vector3D(0,10,0), int maxContacts = 5);
		~MassAggregateSystem();

		void AddParticle(Particle3D* particle, bool hasGravity = true);
		void Update(float deltaTime);
	private:
		ParticleWorld* particleWorld;
		ParticleGravity* gravity;
	};
}


#endif


