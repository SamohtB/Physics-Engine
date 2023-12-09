#include "RigidbodyForceGenerator.h"

using namespace physics;

void RigidbodyForceRegistry::Add(Rigidbody2D* rigidbody, RigidbodyForceGenerator* forceGenerator)
{
	RigidbodyForceRegistration reg = {rigidbody, forceGenerator};
	this->registrations.push_back(reg);
}

void RigidbodyForceRegistry::UpdateForces(float duration)
{
	Registry::iterator i = registrations.begin();
	for(; i != registrations.end(); i++)
	{
		i->forceGenerator->UpdateForce(i->rigidbody, duration);
	}
}

