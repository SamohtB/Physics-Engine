#include "RigidbodySystem.h"

using namespace gamecore;

RigidbodySystem::RigidbodySystem(Vector2D gravity, int maxContacts, float restitution)
{
	this->physicsWorld = new PhysicsWorld(maxContacts);
	this->gravity = new RigidbodyGravity(gravity);
	this->overlapContact = new BoxBoxContactGenerator(0.5f);

	this->floorOffset = 500.0f;
	CollisionFloor floor = CollisionFloor();
	floor.direction = Vector2D(0, -1);
	floor.direction = floor.direction.Normalize();
	floor.offset = -this->floorOffset;

	this->floorContact = new BoxFloorContactGenerator(floor, 0.8f);
}

RigidbodySystem::~RigidbodySystem()
{
	delete this->physicsWorld;
	delete this->gravity;
	delete this->overlapContact;
	delete this->floorContact;
}

void RigidbodySystem::Initialize()
{
	this->physicsWorld->contactGeneratorList.push_back(overlapContact);
	this->physicsWorld->contactGeneratorList.push_back(floorContact);
}


void RigidbodySystem::Update(float deltaTime)
{
	this->physicsWorld->RunPhysics(deltaTime);
}

void RigidbodySystem::AddRigidbody(Box2D* box, bool hasGravity, bool hasOverlap)
{
	this->physicsWorld->rigidbodyList.push_back(&box->body);

	this->physicsWorld->registry.Add(&box->body, this->gravity);

	this->floorContact->collisionList.push_back(&box->collision);
	this->overlapContact->collisionList.push_back(&box->collision);
}

void RigidbodySystem::AttachBoxToBox(Box2D* boxA, Vector2D localConnection, Box2D* boxB, Vector2D otherLocalConnection, float springConstant, float restLength)
{
	RigidbodySpring* spring = new RigidbodySpring(
		localConnection,
		&(boxB->body),
		otherLocalConnection,
		springConstant,		
		restLength);

	this->physicsWorld->registry.Add(&boxA->body, spring);
}




