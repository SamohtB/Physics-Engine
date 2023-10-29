#include "ParticleBungee.h"

using namespace physics;

void ParticleBungee::UpdateForce(Particle3D* particle, float deltaTime)
{
	Vector3D d = particle->GetPosition() - this->other->GetPosition();

	float magnitude = d.GetMagnitude();
	if(magnitude <= this->restLength) { return; }
	magnitude = -springConstant * (magnitude - restLength);

	d = d.Normalize();
	d *= magnitude;
	particle->AddForce(d);
}