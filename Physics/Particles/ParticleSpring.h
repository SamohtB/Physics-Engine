#pragma once
#ifndef PHYSICS_PARTICLE_SPRING_H
#define PHYSICS_PARTICLE_SPRING_H

#include "IParticleForceGenerator.h"

namespace physics
{
    class ParticleSpring : public IParticleForceGenerator
    {
    public:
        ParticleSpring(Particle3D* other, float springConstant, float restLength) : 
			other(other), springConstant(springConstant), restLength(restLength) {}

        virtual void UpdateForce(Particle3D* particle, float deltaTime);

    private:
        Particle3D* other;
        float springConstant;
        float restLength;
    };
}

#endif // !PHYSICS_PARTICLE_SPRING_H


