#include "ParticleContactResolver.h"

using namespace physics;

ParticleContactResolver::ParticleContactResolver(unsigned iterations) : iterations(iterations) {}

void ParticleContactResolver::ResolveContacts(ParticleContact* contactArray, unsigned numContacts, float duration)
{
	for(unsigned i = 0; i < iterations; i++)
	{
		float max = 0.0f;
		unsigned maxIndex = numContacts;

		for(unsigned i = 0; i < numContacts; i++)
		{
			float separationValue = contactArray[i].CalculateSeparatingVelocity();

			if(separationValue < max && (separationValue < 0 || contactArray[i].penetration > 0))
			{
				max = separationValue;
				maxIndex = i;
			}
		}

		if(maxIndex == numContacts)	break;

		contactArray[maxIndex].Resolve(duration);

		Vector3D* move = contactArray[maxIndex].particleMovement;

		for(unsigned j = 0; j < numContacts; j++)
		{
			if(contactArray[j].particles[0] == contactArray[maxIndex].particles[0])
			{
				contactArray[j].penetration -= move[0].Dot(contactArray[j].contactNormal);
			}
			else if(contactArray[j].particles[0] == contactArray[maxIndex].particles[1])
			{
				contactArray[j].penetration -= move[1].Dot(contactArray[j].contactNormal);
			}

			if(contactArray[j].particles[1])
			{
				if(contactArray[j].particles[1] == contactArray[maxIndex].particles[0])
				{
					contactArray[j].penetration += move[0].Dot(contactArray[j].contactNormal);
				}
				else if(contactArray[j].particles[1] == contactArray[maxIndex].particles[1])
				{
					 contactArray[j].penetration += move[1].Dot(contactArray[j].contactNormal);
				}
			}
		}
	}
}

void ParticleContactResolver::SetIterations(unsigned iterations)
{
	this->iterations = iterations;
}
