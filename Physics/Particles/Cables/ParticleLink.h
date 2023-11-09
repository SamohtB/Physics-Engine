#pragma once
#ifndef PHYSICS_PARTICLE_LINK_H
#define PHYSICS_PARTICLE_LINK_H

#include "../Particle3D.h"
#include "ParticleContact.h"
#include "ParticleContactGenerator.h"

namespace physics
{
	class ParticleLink : public ParticleContactGenerator
	{
	public:
		Particle3D* particles[2];

	protected:
		float CurrentLength();
		virtual unsigned FillContact(ParticleContact* contact, unsigned limit) = 0;
	};	
}


#endif


