#pragma once
#ifndef COMPONENT_PARTICLE_SYSTEM_H
#define COMPONENT_PARTICLE_SYSTEM_H

#include "../../../GameCore/Managers/GameObjectManager.h"

#include "../../../BaseClasses/Component.h"
#include "../../../Physics/Particles/ParticleForceRegistry.h"
#include "../../../Physics/Particles/ParticleGravity.h"
#include "../../../Physics/Particles/ParticleDrag.h"
#include "../../ParticleObject.h"

#include "ObjectLifeTime.h"

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
		void Perform();

		void SetMaxParticles(int count);
		void SetLifeTime(float lifeTime);
		void SetGravity(Vector3D gravityVector);
		void SetDrag(float k1, float k2);
		void SetEmissionVector(Vector3D vector);
		void SetEmissionRate(float ratePerSecond);

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

		ParticleForceRegistry* forceRegistry;
		ParticleGravity* gravityGenerator;
		ParticleDrag* dragGenerator;

		Vector3D gravityVector;
		Vector3D emissionVector;

		std::vector<ParticleObject*> pooledParticleObjectList;
	};
}

#endif // !COMPONENT_PARTICLE_SYSTEM_H

