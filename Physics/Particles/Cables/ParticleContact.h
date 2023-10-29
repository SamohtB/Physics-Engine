#pragma once
#ifndef PHYSICS_PARTICLE_CONTACT_H
#define PHYSICS_PARTICLE_CONTACT_H

#include "../Particle3D.h"

namespace physics
{
	class ParticleContact
	{
	friend class ParticleContactResolver;

	public:
		Particle3D* particles[2];
		Vector3D particleMovement[2];

		float restitution;
		float penetration;

		Vector3D contactNormal;
		void Resolve(float deltaTime);

	protected:
		float CalculateSeparatingVelocity();

	private:
		void ResolveVelocity(float duration);
		void ResolveInterpenetration(float deltaTime);
	};
}

#endif // !PHYSICS_PARTICLE_CONTACT_H



