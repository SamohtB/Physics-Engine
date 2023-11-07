#pragma once
#ifndef COMPONENT_PARTICLE_SYSTEM_H
#define COMPONENT_PARTICLE_SYSTEM_H

#include "../../../GameCore/Managers/GameObjectManager.h"

#include "../../../BaseClasses/Component.h"
#include "../../../Physics/Particles/Forces/ParticleForceRegistry.h"
#include "../../../Physics/Particles/Forces/ParticleGravity.h"
#include "../../ParticleObject.h"

#include "../Script/ObjectLifeTime.h"

namespace component
{
	using namespace baseclass;
	using namespace physics;
	using namespace entity;
	using namespace singleton;

	class ParticleSystem : public Component
	{
	public:
		ParticleSystem(std::string name);
		~ParticleSystem();

		void Initialize();
		void Perform() override;

		void SetMaxParticles(int count);
		void SetLifeTime(float lifeTime);
		void SetGravity(Vector3D gravityVector);
		void SetEmissionVector(Vector3D vector);
		void SetEmissionRate(float ratePerSecond);
		void SetParticleImage(sf::Texture* texture);

	private:
		void SpawnParticle();
		void CreateParticlePool();

	private:
		float ticks;
		float emissionRate;
		float particleLifeTime;
		float dragK1;
		float dragK2;
		int maxParticles;

		sf::Texture* texture;

		ParticleForceRegistry* forceRegistry;
		ParticleGravity* gravityGenerator;

		Vector3D gravityVector;
		Vector3D emissionVector;

		std::vector<ParticleObject*> pooledParticleObjectList;
	};
}

#endif // !COMPONENT_PARTICLE_SYSTEM_H

