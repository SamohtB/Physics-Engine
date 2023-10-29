#include "ParticleWorld.h"

using namespace physics;

ParticleWorld::ParticleWorld(unsigned maxContacts, unsigned iterations)
	: maxContacts(maxContacts), resolver(iterations)
{
	particleContactArray = new ParticleContact[maxContacts];
	calculateIterations = (iterations == 0);
}

ParticleWorld::~ParticleWorld()
{
	delete[] particleContactArray;	
}

unsigned ParticleWorld::GenerateContacts()
{
	unsigned limit = maxContacts;
	ParticleContact* particleContactItem = particleContactArray;

	for(auto particleContactGenerator = particleContactGeneratorList.begin(); particleContactGenerator != particleContactGeneratorList.end(); 
		particleContactGenerator++)
	{
		unsigned used = (*particleContactGenerator)->FillContact((particleContactItem), limit);
		limit -= used;
		particleContactItem += used;

		if(limit <= 0) { break; }
	}

	return maxContacts - limit;
}


void ParticleWorld::StartFrame()
{
	for(auto p = particleList.begin(); p != particleList.end(); p++)
	{
		(*p)->ClearAccumulator();
	}
}

void ParticleWorld::Integrate(float deltaTime)
{
	for(auto p = particleList.begin(); p != particleList.end(); p++)
	{
		(*p)->Integrate(deltaTime);
	}
}

void ParticleWorld::RunPhysics(float deltaTime)
{
	StartFrame();
	registry.UpdateForces(deltaTime);	
	Integrate(deltaTime);

	unsigned usedContacts = GenerateContacts();

	if(usedContacts)
	{
		if(calculateIterations)
		{
			resolver.SetIterations(usedContacts * 4);
		}
		resolver.ResolveContacts(particleContactArray, usedContacts, deltaTime);
	}
}


