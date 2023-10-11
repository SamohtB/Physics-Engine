#include "ParticleGravity.h"

using namespace physics;

void ParticleGravity::UpdateForce(Particle3D* particle, float duration)
{
	particle->AddForce(gravity * particle->GetMass());
}