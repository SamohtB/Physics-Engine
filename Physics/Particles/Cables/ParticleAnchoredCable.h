#pragma once
#ifndef PARTICLE_PARTICLE_ANCHORED_CABLE_H
#define PARTICLE_PARTICLE_ANCHORED_CABLE_H

#include "ParticleLink.h"

namespace physics
{
	class ParticleAnchoredCable : public ParticleLink
	{
	public:
		ParticleAnchoredCable(float maxLength, float restitution, Vector3D* anchor) : maxLength(maxLength), restitution(restitution), anchor(anchor) {}
		float maxLength;
		float restitution;
		Vector3D* anchor;
		unsigned FillContact(ParticleContact* contact, unsigned limit) override;
	};
}

#endif



