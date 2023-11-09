#pragma once
#ifndef GAMECORE_MASS_AGGREGATE_SYSTEM
#define GAMECORE_MASS_AGGREGATE_SYSTEM

#include "../Physics/Particles/ParticleWorld.h"
#include "../Physics/Particles/Forces/ParticleGravity.h"
#include "../Physics/Particles/Cables/ParticleOverlapContact.h"
#include "../Physics/Particles/Cables/ParticleGroundContact.h"

namespace gamecore
{
	using namespace physics;

	class MassAggregateSystem
	{
	public:
		MassAggregateSystem(Vector3D gravity = Vector3D(0,100,0), int maxContacts = 5, float restitution = 0.8f);
		~MassAggregateSystem();

		void AddParticle(Particle3D* particle, bool hasGravity = true, bool hasOverlap = true);
		void Update(float deltaTime);

	private:
		ParticleWorld* particleWorld;
		ParticleGravity* gravity;
		ParticleOverlapContact* overlapContact;
		ParticleGroundContact* groundContact;
	};
}


#endif


