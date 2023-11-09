#pragma once
#ifndef PHYSICS_PARTICLE_CABLE_H
#define PHYSICS_PARTICLE_CABLE_H

#include "ParticleLink.h"

namespace physics
{
	class ParticleCable : public ParticleLink
	{
	public:
		ParticleCable(float maxLength, float restitution) : maxLength(maxLength), restitution(restitution) {}
		float maxLength;
		float restitution;
		unsigned FillContact(ParticleContact* contact, unsigned limit) override;
	};
}

#endif


