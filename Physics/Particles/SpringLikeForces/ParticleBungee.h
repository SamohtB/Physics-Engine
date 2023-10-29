#pragma once
#ifndef PHYSICS_PARTICLE_BUNGEE_H
#define PHYSICS_PARTICLE_BUNGEE_H

#include "../Forces/IParticleForceGenerator.h"

namespace physics
{
    class ParticleBungee : public IParticleForceGenerator
    {
    public:
        ParticleBungee(Vector3D* anchor, float springConstant, float restLength) : 
			other(other), springConstant(springConstant), restLength(restLength) {}
        virtual void UpdateForce(Particle3D* particle, float deltaTime);
        
    private:
        Particle3D* other;
        float springConstant;
        float restLength;
    };
}

#endif // !PHYSICS_PARTICLE_BUNGEE_H


