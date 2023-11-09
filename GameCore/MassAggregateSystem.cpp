#include "MassAggregateSystem.h"

using namespace gamecore;

MassAggregateSystem::MassAggregateSystem(Vector3D gravity, int maxContacts, float restitution)
{
	this->particleWorld = new ParticleWorld(maxContacts);
	this->gravity = new ParticleGravity(gravity);
	this->overlapContact = new ParticleOverlapContact(restitution);
	this->groundContact = new ParticleGroundContact(500.0f, restitution);

	this->particleWorld->particleContactGeneratorList.push_back(overlapContact);
	this->particleWorld->particleContactGeneratorList.push_back(groundContact);
}

MassAggregateSystem::~MassAggregateSystem()
{
	delete this->particleWorld;
	delete this->gravity;
	delete this->overlapContact;
	delete this->groundContact;
}


void MassAggregateSystem::Update(float deltaTime)
{
	this->particleWorld->RunPhysics(deltaTime);
}


void MassAggregateSystem::AddParticle(Particle3D* particle, bool hasGravity, bool hasOverlap)
{
	this->particleWorld->particleList.push_back(particle);
	this->groundContact->AddParticle(particle);

	if(hasOverlap)
	{
		this->overlapContact->AddParticle(particle);
	}

	if(hasGravity)
	{
		this->particleWorld->registry.Add(particle, this->gravity);
	}
}



