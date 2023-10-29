#include "ParticleLink.h"

using namespace physics;

float ParticleLink::CurrentLength()
{
	Vector3D relativePos = particles[0]->GetPosition() - particles[1]->GetPosition();
	return relativePos.GetMagnitude();
}
