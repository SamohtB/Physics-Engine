#pragma once
#ifndef PHYSICS_PARTICLE_BOUYANCY_H
#define PHYSICS_PARTICLE_BOUYANCY_H

#include "../Forces/IParticleForceGenerator.h"

namespace physics
{
	class ParticleBouyancy : public IParticleForceGenerator
	{
	public:
		ParticleBouyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1000.0f) :
			maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity) {}

		virtual void UpdateForce(Particle3D* particle, float deltaTime);

	private:
		float maxDepth;
		float volume;
		float waterHeight;
		float liquidDensity;
	};
}


#endif // !PHYSICS_PARTICLE_BOUYANCY_H



