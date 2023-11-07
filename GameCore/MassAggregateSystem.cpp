#include "MassAggregateSystem.h"

using namespace gamecore;

MassAggregateSystem::MassAggregateSystem(Vector3D gravity, int maxContacts)
{
	this->particleWorld = new ParticleWorld(maxContacts);
	this->gravity = new ParticleGravity(gravity);
}

MassAggregateSystem::~MassAggregateSystem()
{
	delete this->particleWorld;
	delete this->gravity;
}


void MassAggregateSystem::Update(float deltaTime)
{
	this->particleWorld->RunPhysics(deltaTime);
}


void MassAggregateSystem::AddParticle(Particle3D* particle, bool hasGravity)
{
	this->particleWorld->particleList.push_back(particle);

	if(hasGravity)
	{
		this->particleWorld->registry.Add(particle, this->gravity);
	}
}



