#pragma once
#ifndef GAMECORE_RIGIDBODY_SYSTEM_H
#define GAMECORE_RIGIDBODY_SYSTEM_H

#include "../Entities/Box2D.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/Rigidbodies/RigidbodyGravity.h"
#include "../Physics/Rigidbodies/NarrowPhase.h"
#include "../Physics/Rigidbodies/RigidbodyContact.h"
#include "../Physics/Rigidbodies/RigidbodySpring.h"
#include "../Physics/Rigidbodies/RigidbodyForceGenerator.h"

namespace gamecore
{
	using namespace baseclass;
	using namespace physics;
	using namespace entity;

	class RigidbodySystem
	{
	public:
		RigidbodySystem(Vector2D gravity = Vector2D(0, 980.0f), int maxContacts = 64, float restitution = 0.5f);
		~RigidbodySystem();

		void AttachBoxToBox(Vector2D localConnection, Box2D* box, Vector2D otherLocalConnection, float springConstant, float restitution);
		void AddRigidbody(Box2D* box, bool hasGravity = true, bool hasOverlap = true);
		void Update(float deltaTime);

	private:
		PhysicsWorld* physicsWorld;
		RigidbodyGravity* gravity;
		BoxBoxContactGenerator* overlapContact;
		BoxFloorContactGenerator* floorContact;

		CollisionFloor* floor;
		std::vector<CollisionData*> dataList;
	};

}

#endif


