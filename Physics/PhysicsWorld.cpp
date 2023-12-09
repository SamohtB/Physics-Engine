#include "PhysicsWorld.h"

using namespace physics;

unsigned BoxFloorContactGenerator::AddContact(RigidbodyContact* contact, unsigned limit)
{
	unsigned count = 0;

	for(auto cBox = collisionList.begin(); cBox != collisionList.end(); cBox++)
	{
		CollisionData cData;
		cData.contactsLeft = limit;
		cData.contactCount = 0;
		cData.contactsArray = contact;
		cData.contacts = contact;
		cData.restitution = restitution;

		unsigned colCnt = CollisionDetector::BoxAndHalfSpace((**cBox), this->collisionFloor, &cData);
		contact += colCnt;
		count += colCnt;
		if(count > limit) { return count; }
	}

	return count;
}

unsigned BoxBoxContactGenerator::AddContact(RigidbodyContact* contact, unsigned limit)
{
	unsigned count = 0;

	for(auto cBox1 = collisionList.begin(); cBox1 != collisionList.end(); cBox1++)
	{
		for(auto cBox2 = cBox1 + 1; cBox2 != collisionList.end(); cBox2++)
		{
			CollisionData cData;
			cData.contactsLeft = limit;
			cData.contactCount = 0;
			cData.contactsArray = contact;
			cData.contacts = contact;
			cData.restitution = restitution;

			unsigned colCnt = CollisionDetector::BoxAndBox((**cBox1), (**cBox2), &cData);
			contact += colCnt;
			count += colCnt;
			if (count > limit) { return count; }
		}
	}

	return count;
}

PhysicsWorld::PhysicsWorld(unsigned maxContacts, unsigned iterations) : maxContacts(maxContacts)
{
	calculateIterations = (iterations == 0);
	rigidbodyContactArray = new RigidbodyContact[maxContacts];
}

PhysicsWorld::~PhysicsWorld()
{
	delete[] rigidbodyContactArray;
}

void PhysicsWorld::StartFrame()
{
	for(auto r = rigidbodyList.begin(); r != rigidbodyList.end(); r++)
	{
		(*r)->ClearAccumulator();
	}
}

void PhysicsWorld::Integrate(float deltaTime)
{
	for(auto r = rigidbodyList.begin(); r != rigidbodyList.end(); r++)
	{
		(*r)->Integrate(deltaTime);
	}
}

void PhysicsWorld::RunPhysics(float deltaTime)
{
	//StartFrame();
	registry.UpdateForces(deltaTime);	
	Integrate(deltaTime);

	unsigned usedContacts = GenerateContacts();

	if(usedContacts)
	{
		resolver.ResolveContacts(rigidbodyContactArray, usedContacts, deltaTime);
	}
}

unsigned PhysicsWorld::GenerateContacts()
{
	unsigned limit = maxContacts;
	RigidbodyContact* nextContact = rigidbodyContactArray;

	for(auto reg = contactGeneratorList.begin(); reg != contactGeneratorList.end(); reg++)
	{
		unsigned used = (*reg)->AddContact(nextContact, limit);
		limit -= used;

		if(limit <= 0) { break; }
	}

	return maxContacts - limit;
}

