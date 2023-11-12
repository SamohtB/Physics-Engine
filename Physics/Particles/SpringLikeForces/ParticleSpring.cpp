#include "ParticleSpring.h"

using namespace physics;

void ParticleSpring::UpdateForce(Particle3D* particle, float deltaTime)
{
	Vector3D d = particle->GetPosition() - this->other->GetPosition();

	float magnitude = d.GetMagnitude();
	magnitude = -springConstant * (magnitude - restLength);

	d = d.Normalize();
	d *= magnitude;
	particle->AddForce(d);
}