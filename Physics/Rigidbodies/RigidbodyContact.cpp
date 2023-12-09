#include "RigidbodyContact.h"

using namespace physics;

void RigidbodyContact::CalculateInternals(float deltaTime)
{
	relativeContactPosition[0] = contactPoint - body[0]->GetPosition();

	if(body[1])
	{
		relativeContactPosition[1] = contactPoint - body[1]->GetPosition();
	}

	float totalInverseMass = body[0]->GetInverseMass();
	Vector2D relativePositionAPerpendicular = Vector2D(-relativeContactPosition[0].y, relativeContactPosition[0].x);
	float relativePositionAPerpendicularDot = relativePositionAPerpendicular.Dot(contactNormal);
	totalInverseMass += (relativePositionAPerpendicularDot * relativePositionAPerpendicularDot) / body[0]->GetInertiaTensor();

	Vector2D relativeVelocity = CalculateLocalVelocity(0, deltaTime);

	if(body[1])
	{
		totalInverseMass += body[1]->GetInverseMass();
		Vector2D relativePositionBPerpendicular = Vector2D(-relativeContactPosition[1].y, relativeContactPosition[1].x);
		float relativePositionBPerpendicularDot = relativePositionBPerpendicular.Dot(contactNormal);
		totalInverseMass += (relativePositionBPerpendicularDot * relativePositionBPerpendicularDot) / body[1]->GetInertiaTensor();

		relativeVelocity -= CalculateLocalVelocity(1, deltaTime);
	}

	float contactSeparatingMagnitude = relativeVelocity.Dot(contactNormal);
	float newSeparatingMagnitude = -this->restitution * contactSeparatingMagnitude;
	float deltaVelocity =  newSeparatingMagnitude - contactSeparatingMagnitude;

	impulseMagnitude = deltaVelocity / totalInverseMass;
}

Vector2D RigidbodyContact::CalculateLocalVelocity(unsigned bodyIndex, float deltaTime)
{
	Rigidbody2D* thisBody = body[bodyIndex];

	Vector2D linerVelocity = thisBody->GetVelocity();
	Vector2D relativePos = relativeContactPosition[bodyIndex];

	Vector2D relativePositionPerpendicular = Vector2D(-relativePos.y, relativePos.x);
	Vector2D tagentialVelocity = relativePositionPerpendicular * thisBody->angularVelocity;

	return linerVelocity + tagentialVelocity;
}

void RigidbodyContact::ApplyImpulse()
{
	Vector2D impulse = contactNormal * impulseMagnitude;

	Vector2D changeInVelocityA = impulse * body[0]->GetInverseMass();
	body[0]->SetVelocity(body[0]->GetVelocity() + changeInVelocityA);
	body[0]->angularVelocity += relativeContactPosition[0].Cross(impulse) / body[0]->GetInertiaTensor();

	if(body[1])
	{
		Vector2D changeInVelocityB = impulse * -body[1]->GetInverseMass();
		body[1]->SetVelocity(body[1]->GetVelocity() + changeInVelocityB);
		body[1]->angularVelocity -= relativeContactPosition[1].Cross(impulse) / body[1]->GetInertiaTensor();
	}
}

void RigidbodyContactResolver::ResolveContacts(RigidbodyContact* contactArray, unsigned numContact, float deltaTime)
{
	for(int i = 0; i < numContact; i++)
	{
		RigidbodyContact* contact = contactArray + i;
		contact->CalculateInternals(deltaTime);
		contact->ApplyImpulse();
	}
}



