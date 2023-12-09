#include "RigidbodySpring.h"

using namespace physics;

void RigidbodySpring::UpdateForce(Rigidbody2D* rigidbody, float duration)
{
	Vector2D transformedLocal = rigidbody->GetPointInWorldSpace(localConnection);
	Vector2D transformedOther = other->GetPointInWorldSpace(otherLocalConnection);

	Vector2D d = transformedLocal - transformedOther;

	float magnitude = d.GetMagnitude();

	magnitude = -springConstant * (magnitude - restLength);

	d = d.Normalize();
	d *= magnitude;

	transformedLocal = transformedLocal - rigidbody->GetPosition();
	rigidbody->AddForceOnPoint(transformedLocal, d);
}
