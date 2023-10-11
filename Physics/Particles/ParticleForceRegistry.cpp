#include "ParticleForceRegistry.h"

using namespace physics;

void ParticleForceRegistry::UpdateForces(float deltaTime)
{
	Registry::iterator i = registrations.begin();
	for(; i != registrations.end(); i++)
	{
		i->forceGenerator->UpdateForce(i->particle, deltaTime);
	}
}

void ParticleForceRegistry::Add(Particle3D* particle, IParticleForceGenerator* forceGenerator)
{
	ParticleForceRegistration reg = {particle, forceGenerator};
	this->registrations.push_back(reg);
}