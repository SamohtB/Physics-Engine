#include "RigidbodySystem.h"

using namespace gamecore;

RigidbodySystem::RigidbodySystem(Vector2D gravity, int maxContacts, float restitution)
{
	this->physicsWorld = new PhysicsWorld(maxContacts);
	this->gravity = new RigidbodyGravity(gravity);
	this->overlapContact = new BoxBoxContactGenerator(restitution);

	floor = new CollisionFloor();
	floor->direction = Vector2D(0, -1.0f);
	floor->offset = 500.0f;

	this->floorContact = new BoxFloorContactGenerator(*floor, restitution);
	this->physicsWorld->contactGeneratorList.push_back(overlapContact);
	this->physicsWorld->contactGeneratorList.push_back(floorContact);
}

RigidbodySystem::~RigidbodySystem()
{
	delete this->physicsWorld;
	delete this->gravity;
	delete this->overlapContact;
	delete this->floor;
	delete this->floorContact;
}

void RigidbodySystem::Update(float deltaTime)
{
	this->physicsWorld->RunPhysics(deltaTime);
}

void RigidbodySystem::AddRigidbody(Rigidbody2D* rigidbody, bool hasGravity, bool hasOverlap)
{
	this->physicsWorld->rigidbodyList.push_back(rigidbody);

	if(hasGravity)
	{
		this->physicsWorld->registry.Add(rigidbody, this->gravity);
	}
}



