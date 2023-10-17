#include "ParticleSystem.h"

using namespace component;

ParticleSystem::ParticleSystem(std::string name) : Component(name, ComponentType::PHYSICS)
{
	// Default Values
	this->maxParticles = 25;
	this->gravityVector = Vector3D(0.0f, 250.0f, 0.0f);
	this->dragK1 = 0.0f;
	this->dragK2 = 0.0f;
	this->particleLifeTime = 2.0f;
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
	this->particleLifeTime = lifeTime;
}

void ParticleSystem::CreateParticlePool()
{
	ParticleObject* particle; 
	Vector3D position = this->GetOwner()->GetPosition();

	for(int i = 0; i < maxParticles; i++)
	{
		particle = new ParticleObject("Particle_" + std::to_string(i));

		this->pooledParticleObjectList.push_back(particle);
		GameObjectManager::GetInstance()->AddObject(particle);

		particle->SetPosition(position);
		particle->SetEnabledStatus(true);

		this->forceRegistry->Add(particle->GetParticle(), this->dragGenerator);
		this->forceRegistry->Add(particle->GetParticle(), this->gravityGenerator);

		ObjectLifeTime* lifeTimeScript = new ObjectLifeTime(this->GetName() + " Life Time", this->particleLifeTime);
		particle->AttachComponent(lifeTimeScript);
	}
}

void ParticleSystem::SetGravity(Vector3D gravityVector)
{
	this->gravityVector = gravityVector;
}

void ParticleSystem::SetDrag(float k1, float k2)
{
	this->dragK1 = k1;
	this->dragK2 = k2;
}