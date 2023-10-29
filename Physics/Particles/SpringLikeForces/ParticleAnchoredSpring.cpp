#include "ParticleAnchoredSpring.h"

using namespace physics;

void ParticleAnchoredSpring::UpdateForce(Particle3D* particle, float deltaTime)
{
	Vector3D d = particle->GetPosition() - *anchor;
	float magnitude = d.GetMagnitude();

	magnitude = -springConstant * (magnitude - restLength);

	d = d.Normalize();
	d *= magnitude;

	particle->AddForce(d);
}