#pragma once
#ifndef PHYSICS_PARTICLE_ANCHORED_SPRING_H
#define PHYSICS_PARTICLE_ANCHORED_SPRING_H

#include "IParticleForceGenerator.h"

namespace physics
{
	class ParticleAnchoredSpring : public IParticleForceGenerator
	{
	public:
		ParticleAnchoredSpring(Vector3D* anchor, float springConstant, float restLength) : 
			anchor(anchor), springConstant(springConstant), restLength(restLength) {}

		virtual void UpdateForce(Particle3D* particle, float deltaTime);
		
	private:
		Vector3D* anchor;
		float springConstant;
		float restLength;
	};
}



#endif // !PHYSICS_PARTICLE_ANCHORED_SPRING_H


