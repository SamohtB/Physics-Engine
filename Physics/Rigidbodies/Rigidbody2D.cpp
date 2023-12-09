#include "Rigidbody2D.h"

using namespace physics;

void Rigidbody2D::AddForceOnPoint(Vector2D point, Vector2D force)
{
	this->forceAccumulator += force;
	this->torqueAccumulator += point.Cross(force);
}

void Rigidbody2D::Integrate(float deltaTime)
{
	Particle2D::Integrate(deltaTime);

	this->rotation += this->angularVelocity * deltaTime;

	float intertiaTensor = this->shape->GetInertiaTensor(this->GetMass());

	this->angularVelocity += this->torqueAccumulator * (1.0f / intertiaTensor) * deltaTime;

	this->angularVelocity *= std::pow(this->angularDamping, deltaTime);

	this->ClearTorqueAccumulator();
}

void Rigidbody2D::ClearTorqueAccumulator()
{
	this->torqueAccumulator = 0.0f;	
}

Vector2D Rigidbody2D::GetPointInWorldSpace(Vector2D point)
{
	sf::Vector2f temp = this->transformMatrix.transformPoint(point.x, point.y);
	return Vector2D(temp.x, temp.y);
}

float Rigidbody2D::GetInertiaTensor()
{
	return this->shape->GetInertiaTensor(this->GetMass());
}



