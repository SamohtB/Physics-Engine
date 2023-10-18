#include "ParticleSystem.h"

using namespace component;

ParticleSystem::ParticleSystem(std::string name) : Component(name, ComponentType::PHYSICS)
{
	// Default Values
	this->maxParticles = 25;
	this->dragK1 = 0.1f;
	this->dragK2 = 0.2f;
	this->ticks = 0.0f;
	this->emissionRate = 1.0f;
	this->particleLifeTime = 5.0f;

	this->gravityVector = Vector3D(0.0f, 100.f, 0.0f);
	this->emissionVector = Vector3D(0.0f, -100.f, 0.0f);
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

	CreateParticlePool();
}

void ParticleSystem::Perform()
{
	this->ticks += this->deltaTime.asSeconds();

	if(this->ticks >= 1 / this->emissionRate)
	{
		this->ticks = 0.0f;
		this->SpawnParticle();
	}

	forceRegistry->UpdateForces(this->deltaTime.asSeconds());
}

void ParticleSystem::SpawnParticle()
{
	for(ParticleObject* particle : this->pooledParticleObjectList)
	{
		if(particle->GetEnabledStatus() == false)
		{
			particle->SetEnabledStatus(true);
			particle->Reset();
			particle->SetPosition(this->GetOwner()->GetPosition());

			particle->GetParticle()->AddForce(this->emissionVector * 20);
			break;
		}
	}

	//std::cerr << "REACHED PARTICLE LIMIT" << std::endl;
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
		particle->SetEnabledStatus(false);

		particle->GetParticle()->SetDamping(1.f);

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

void ParticleSystem::SetEmissionVector(Vector3D vector)
{
	this->emissionVector = vector;
}

void ParticleSystem::SetEmissionRate(float ratePerSecond)
{
	this->emissionRate = ratePerSecond;
}