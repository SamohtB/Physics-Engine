#include "ParticleCable.h"

using namespace physics;

unsigned ParticleCable::FillContact(ParticleContact* contact, unsigned limit)
{
	assert(limit > 0);
	float length = CurrentLength();

	if(length < maxLength)
	{
		return 0;
	}

	contact->particles[0] = particles[0];
	contact->particles[1] = particles[1];

	Vector3D normal = particles[1]->GetPosition() - particles[0]->GetPosition();
	normal = normal.Normalize();

	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}
