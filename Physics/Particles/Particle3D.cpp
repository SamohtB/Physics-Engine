#include "Particle3D.h"

using namespace physics;

Particle3D::Particle3D()
{
	this->inverseMass = 1;
	this->damping = 0.99f;

	this->position = Vector3D();
	this->velocity = Vector3D();
	this->acceleration = Vector3D();
	this->forceAccumulator = Vector3D();
}

void Particle3D::Integrate(float deltaTime)
{
	this->position += this->velocity * deltaTime;

	Vector3D resultingAcceleration = this->acceleration;
	resultingAcceleration += forceAccumulator * inverseMass;
	this->velocity += this->acceleration + resultingAcceleration * deltaTime;

	this->velocity *= std::powf(damping, deltaTime);
	this->ClearAccumulator();
}

void Particle3D::AddForce(Vector3D force)
{
	this->forceAccumulator += force;
}

void Particle3D::SetDamping(float damping)
{
	this->damping = damping;
}

float Particle3D::GetDamping()
{
	return this->damping;
}

void Particle3D::SetMass(float mass)
{
	assert(mass != 0);
	this->inverseMass = 1.0f / mass;
}

float Particle3D::GetMass()
{
	if(this->inverseMass == 0)
	{
		return FLT_MAX;
	}

	return 1.0f / this->inverseMass;
}
		
void Particle3D::SetVelocity(Vector3D velocity)
{
	this->velocity = velocity;
}

Vector3D Particle3D::GetVelocity()
{
	return this->velocity;
}

void Particle3D::SetAcceleration(Vector3D acceleration)
{
	this->acceleration = acceleration;
}

Vector3D Particle3D::GetAcceleration()
{
	return this->acceleration;
}

void Particle3D::SetPosition(Vector3D position)
{
	this->position = position;
}

Vector3D Particle3D::GetPosition()
{
	return this->position;
}

Vector3D* Particle3D::GetPositionReference()
{
	return &this->position;
}

void Particle3D::ClearAccumulator()
{
	this->forceAccumulator.Zero();
}


