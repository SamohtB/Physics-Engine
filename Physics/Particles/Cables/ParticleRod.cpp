#include "ParticleRod.h"

using namespace  physics;

unsigned ParticleRod::FillContact(ParticleContact* contact, unsigned limit)
{
	assert(limit > 0);
	float currentLength = CurrentLength();

	if(currentLength == length)
	{
		return 0;
	}

	contact->particles[0] = particles[0];
	contact->particles[1] = particles[1];

	Vector3D normal = particles[1]->GetPosition() - particles[0]->GetPosition();
	normal = normal.Normalize();

	if(currentLength > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLength - length;
	}
	else
	{
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLength;
	}

	contact->restitution = 0.0f;

	return 1;
}
