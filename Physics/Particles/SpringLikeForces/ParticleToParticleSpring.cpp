//#include "ParticleToParticleSpring.h"
//
//using namespace physics;
//
//void ParticleToParticleSpring::UpdateForce(Particle3D* particle, Particle3D* particle2, float deltaTime)
//{
//	Vector3D d = particle->GetPosition() - particle2->GetPosition();
//	
//	float magnitude = d.GetMagnitude();
//	magnitude = -springConstant * (magnitude - restLength);
//
//	d = d.Normalize();
//	d *= magnitude;
//	particle->AddForce(d);
//}