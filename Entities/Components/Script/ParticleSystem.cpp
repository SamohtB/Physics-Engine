#include "ParticleSystem.h"

using namespace component;

ParticleSystem::ParticleSystem(std::string name) : Component(name, ComponentType::SCRIPT)
{
	// Default Values
	this->lifeTime = 5.0f;
	this->ticks = 0.0f;
	this->maxParticles = 25;
	this->gravityVector = Vector3D(0.0f, 10.0f, 0.0f);
	this->dragK1 = 0.5f;
	this->dragK2 = 1.0f;
}

ParticleSystem::~ParticleSystem()
{
	delete this->forceRegistry;
	delete this->gravityGenerator;
	delete this->dragGenerator;

	for(ParticleObject* particle : this->pooledParticleObjectList)
	{
		delete particle;
	}

	this->pooledParticleObjectList.clear();
}

void ParticleSystem::Initialize()
{
	this->forceRegistry = new ParticleForceRegistry();
	this->gravityGenerator = new ParticleGravity(this->gravityVector);
	this->dragGenerator = new ParticleDrag(this->dragK1, this->dragK2);

	CreateParticlePool();
}

void ParticleSystem::Perform()
{
	forceRegistry->UpdateForces(this->deltaTime.asSeconds());
}

void ParticleSystem::SetMaxParticles(int count)
{
	this->maxParticles = count;
	this->CreateParticlePool();
}

void ParticleSystem::SetLifeTime(float lifeTime)
{
	this->lifeTime = lifeTime;
}

void ParticleSystem::CreateParticlePool()
{
	ParticleObject* particle; 

	for(int i = 0; i < maxParticles; i++)
	{
		particle = new ParticleObject("Particle_" + std::to_string(i));
		this->pooledParticleObjectList.push_back(particle);
		GameObjectManager::GetInstance()->AddObject(particle);
		particle->SetEnabledStatus(false);
	}
}