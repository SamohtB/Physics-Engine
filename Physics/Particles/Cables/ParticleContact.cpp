#include "ParticleContact.h"

using namespace physics;

void ParticleContact::Resolve(float deltaTime)
{
	ResolveVelocity(deltaTime);
	ResolveInterpenetration(deltaTime);
}

float ParticleContact::CalculateSeparatingVelocity()
{
	Vector3D relativeVelocity = this->particles[0]->GetVelocity();

	if(particles[1]) 
	{
		relativeVelocity -= particles[1]->GetVelocity();
	}

	return relativeVelocity.Dot(this->contactNormal);
}

void ParticleContact::ResolveVelocity(float duration)
{
	float separatingVelocity = CalculateSeparatingVelocity();

	if(separatingVelocity > 0)	{ return; }

	float newSeparatingVelocity = -restitution * separatingVelocity;

	float deltaVelocity = newSeparatingVelocity - separatingVelocity;
	float totalInverseMass = this->particles[0]->GetInverseMass();
	
	if(this->particles[1])
	{
		totalInverseMass +=	particles[1]->GetInverseMass();
	}

	if(totalInverseMass <= 0) { return; }

	float impulseMagnitude = deltaVelocity / totalInverseMass;
	Vector3D impulse = contactNormal * impulseMagnitude;

	Vector3D changeInVelocityA = impulse * particles[0]->GetInverseMass();
	particles[0]->SetVelocity(particles[0]->GetVelocity() + changeInVelocityA);

	if(particles[1])
	{
		Vector3D changeInVelocityB = impulse * -particles[1]->GetInverseMass();
		particles[1]->SetVelocity(particles[1]->GetVelocity() + changeInVelocityB);
	}
}

void ParticleContact::ResolveInterpenetration(float deltaTime)
{
	if(penetration <= 0) { return; }

	float totalMass = this->particles[0]->GetMass();

	if(this->particles[1])
	{
		totalMass += particles[1]->GetMass();
	}

	Vector3D movePerIMass = this->contactNormal * (penetration / totalMass);

	particleMovement[0] = movePerIMass * particles[0]->GetMass();
	particles[0]->SetPosition(particles[0]->GetPosition() + particleMovement[0]);
	
	if(particles[1])
	{
		particleMovement[1] = movePerIMass * -particles[1]->GetMass();
		particles[1]->SetPosition(particles[1]->GetPosition() + particleMovement[1]);
	}
	else
	{
		particleMovement[1].Zero();
	}
}