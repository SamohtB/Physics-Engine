#pragma once
#ifndef PHYSICS_PARTICLE_CONTACT_GENERATOR_H
#define PHYSICS_PARTICLE_CONTACT_GENERATOR_H

#include "ParticleContact.h"

namespace physics
{
	class ParticleContactGenerator
	{
	public:
		virtual unsigned FillContact(ParticleContact* contact, unsigned limit) = 0;
	};
}

#endif

