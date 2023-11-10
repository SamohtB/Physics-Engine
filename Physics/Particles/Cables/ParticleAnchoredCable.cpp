#include "ParticleAnchoredCable.h"

using namespace physics;

unsigned ParticleAnchoredCable::FillContact(ParticleContact* contact, unsigned limit)
{
	assert(limit > 0);
	Vector3D vecLength = particles[0]->GetPosition() - *this->anchor;
	float length = vecLength.GetMagnitude();

	if(length < maxLength)
	{
		return 0;
	}

	contact->particles[0] = particles[0];
	contact->particles[1] = nullptr;

	Vector3D normal = *this->anchor - particles[0]->GetPosition();
	normal = normal.Normalize();

	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}