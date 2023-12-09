#include "Particle2D.h"

using namespace physics;

Particle2D::Particle2D()
{
	this->mass = 1;
	this->inverseMass = 1;
	this->damping = 0.99f;
	this->radius = 0.0f;

	this->position = Vector2D();
	this->velocity = Vector2D();
	this->acceleration = Vector2D();
	this->forceAccumulator = Vector2D();
}

void Particle2D::Integrate(float deltaTime)
{
	this->position += this->velocity * deltaTime;

	Vector2D resultingAcceleration = this->acceleration;
	resultingAcceleration += forceAccumulator * inverseMass;
	this->velocity += this->acceleration + resultingAcceleration * deltaTime;

	this->velocity *= std::powf(damping, deltaTime);
	this->ClearAccumulator();
}

void Particle2D::AddForce(Vector2D force)
{
	this->forceAccumulator += force;
}

void Particle2D::SetDamping(float damping)
{
	this->damping = damping;
}

float Particle2D::GetDamping()
{
	return this->damping;
}

void Particle2D::SetMass(float mass)
{
	assert(mass != 0);
	this->inverseMass = 1.0f / mass;
	this->mass = mass;
}

float Particle2D::GetMass()
{
	return this->mass;
}

float Particle2D::GetInverseMass()
{
	return this->inverseMass;
}
		
void Particle2D::SetVelocity(Vector2D velocity)
{
	this->velocity = velocity;
}

Vector2D Particle2D::GetVelocity()
{
	return this->velocity;
}

void Particle2D::SetAcceleration(Vector2D acceleration)
{
	this->acceleration = acceleration;
}

Vector2D Particle2D::GetAcceleration()
{
	return this->acceleration;
}

void Particle2D::SetPosition(Vector2D position)
{
	this->position = position;
}

Vector2D Particle2D::GetPosition()
{
	return this->position;
}

Vector2D* Particle2D::GetPositionReference()
{
	return &this->position;
}

void Particle2D::ClearAccumulator()
{
	this->forceAccumulator.Zero();
}

void Particle2D::SetRadius(float radius)
{
	this->radius = radius;
}

float Particle2D::GetRadius()
{
	return this->radius;
}



