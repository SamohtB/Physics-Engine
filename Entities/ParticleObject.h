#pragma once
#ifndef ENTITY_PARTICLE_OBJECT_H
#define ENTITY_PARTICLE_OBJECT_H

#include "../BaseClasses/GameObject.h"
#include "Components/Renderer/Renderer.h"
#include "../Physics/Particles/Particle3D.h"

namespace entity
{
	using namespace baseclass;
	using namespace physics;

	class ParticleObject : public GameObject
	{
	public:
		ParticleObject(std::string name);
		void Initialize();

		Vector3D GetPosition() override;
		void SetPosition(Vector3D position) override;
		void Move(Vector3D displacement) override;
		void PhysicsUpdate(sf::Time deltaTime) override;

		Particle3D* GetParticle();
		void SetEnabledStatus(bool status) override;

	private:
		sf::CircleShape* renderedObject;
		Particle3D* particle;

	};
}


#endif // !ENTITY_PARTICLE_OBJECT_H



