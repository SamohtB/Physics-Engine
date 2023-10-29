#include "ParticleOverlapContact.h"

using namespace physics;

ParticleOverlapContact::ParticleOverlapContact(float restitution) : restitution(restitution) {}

unsigned ParticleOverlapContact::FillContact(ParticleContact* contact, unsigned limit)
{
	unsigned count = 0;
	for(auto p1 = particleList.begin(); p1 != particleList.end(); p1++)
	{
		for(auto p2 = p1 + 1; p2 != particleList.end(); p2++)
		{
			Vector3D distanceVector = (*p1)->GetPosition() - (*p2)->GetPosition();
			float distance = (distanceVector).GetMagnitude() - (*p1)->GetRadius() - (*p2)->GetRadius();

			if(distance < 0.0f)
			{
				distanceVector = distanceVector.Normalize();
				contact->contactNormal = distanceVector;
				contact->particles[0] = (*p1);
				contact->particles[1] = (*p2);
				contact->penetration = -distance;
				contact->restitution = restitution;
				contact++;
				count++;
			}

			if(count >= limit)
			{
				return count;
			}
		}
	}

	return count;
}

void ParticleOverlapContact::AddParticle(Particle3D* particle)
{
	this->particleList.push_back(particle);
}
