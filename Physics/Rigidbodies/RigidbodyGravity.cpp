#include "RigidbodyGravity.h"

using namespace physics;

void RigidbodyGravity::UpdateForce(Rigidbody2D* rigidbody, float duration)
{
	rigidbody->AddForce(gravity * rigidbody->GetMass());
}
