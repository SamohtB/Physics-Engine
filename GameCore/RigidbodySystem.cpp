#include "RigidbodySystem.h"

using namespace gamecore;

RigidbodySystem::RigidbodySystem(Vector2D gravity, int maxContacts, float restitution)
{
	this->physicsWorld = new PhysicsWorld(maxContacts);
	this->gravity = new RigidbodyGravity(gravity);
	this->overlapContact = new BoxBoxContactGenerator(restitution);

	floor = new CollisionFloor();
	floor->direction = Vector2D(0, -1);
	floor->offset = -600.0f;

	this->floorContact = new BoxFloorContactGenerator(*floor, 0.8f);
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

void RigidbodySystem::AddRigidbody(Box2D* box, bool hasGravity, bool hasOverlap)
{
	this->physicsWorld->rigidbodyList.push_back(&box->body);

	if(hasGravity)
	{
		this->physicsWorld->registry.Add(&box->body, this->gravity);
	}

	if(hasOverlap)
	{
		//this->floorContact->collisionList.push_back(&box->collision);
		//this->overlapContact->collisionList.push_back(&box->collision);
	}
}

void RigidbodySystem::AttachBoxToBox(Vector2D localConnection, Box2D* box, Vector2D otherLocalConnection, float springConstant, float restitution)
{
	RigidbodySpring* spring = new RigidbodySpring(
		localConnection,
		&box->body,
		otherLocalConnection,
		springConstant, 
		restitution);

	this->physicsWorld->registry.Add(&box->body, spring);
}




