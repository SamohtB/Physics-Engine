#pragma once
#ifndef PHYSICS_PHYSICS_WORLD_H
#define PHYSICS_PHYSICS_WORLD_H

#include <vector>

#include "Rigidbodies/Rigidbody2D.h"
#include "Rigidbodies/RigidbodyForceGenerator.h"
#include "Rigidbodies/RigidbodyContact.h"
#include "Rigidbodies/NarrowPhase.h"

namespace  physics
{
	class RigidbodyContactGenerator
	{
	public:
		virtual unsigned AddContact(RigidbodyContact* contact, unsigned limit) = 0;
	};

	class BoxFloorContactGenerator : public RigidbodyContactGenerator
	{
	public:
		std::vector<CollisionBox*> collisionList;
		BoxFloorContactGenerator(CollisionFloor floor, float restitution) :	collisionFloor(floor), restitution(restitution) {}

		virtual unsigned AddContact(RigidbodyContact* contact, unsigned limit) override;

	private:
		float restitution;
		CollisionFloor collisionFloor;
	};

	class BoxBoxContactGenerator : public RigidbodyContactGenerator
	{
	public:
		std::vector<CollisionBox*> collisionList;
		BoxBoxContactGenerator(float restitution) : restitution(restitution) {}

		virtual unsigned AddContact(RigidbodyContact* contact, unsigned limit) override;

	private:
		float restitution;
	};



	class PhysicsWorld
	{
	public:
		PhysicsWorld(unsigned maxContacts, unsigned iterations = 0);
		~PhysicsWorld();

		void StartFrame();
		void Integrate(float deltaTime);
		void RunPhysics(float deltaTime);

		unsigned maxContacts;
		bool calculateIterations;

		std::vector<Rigidbody2D*> rigidbodyList;
		RigidbodyForceRegistry registry;
		RigidbodyContactResolver resolver;
		std::vector<RigidbodyContactGenerator*> contactGeneratorList;
		RigidbodyContact* rigidbodyContactArray;

		unsigned GenerateContacts();
	};
}

#endif


