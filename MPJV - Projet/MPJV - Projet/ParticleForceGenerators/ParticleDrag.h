#pragma once
#include "ParticleForceGenerator.h"
class ParticleDrag :
    public ParticleForceGenerator
{
private:
    //drag coefficients
    float m_k1, m_k2;

public:
    virtual void UpdateForce(Particle* particle, float deltaTime);

};

