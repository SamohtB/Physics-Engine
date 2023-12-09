#pragma once
#ifndef PHYSICS_NARROW_PHASE_H
#define PHYSICS_NARROW_PHASE_H

#include "Rigidbody2D.h"
#include "RigidbodyContact.h"

namespace physics
{
	struct CollisionData
	{
		RigidbodyContact* contactsArray;
		RigidbodyContact* contacts;
		int contactsLeft;
		unsigned contactCount;
		float restitution;

		void AddContacts(unsigned count)
		{
			contactsLeft -= count;
			contactCount += count;
			contacts += count;
		}
	};

	class CollisionFloor
	{
	public:
		Vector2D direction;
		float offset;
	};

	class CollisionPrimitive
	{
	public:
		Rigidbody2D* body;
		Vector2D GetAxisVector(int i);
	};

	class CollisionBox : public CollisionPrimitive
	{
	public:
		Vector2D halfSize;
	};

	class IntersectionTests
	{
	public:
		static bool BoxAndHalfSpace(CollisionBox& box, CollisionFloor& floor);
		static bool BoxAndBox(CollisionBox& one, CollisionBox& two);
	};

	class CollisionDetector
	{
	public:
		static unsigned BoxAndHalfSpace(CollisionBox &box, CollisionFloor &floor, CollisionData* data);
		static unsigned BoxAndBox(CollisionBox &one, CollisionBox &two, CollisionData* data);
	};
}

#endif



