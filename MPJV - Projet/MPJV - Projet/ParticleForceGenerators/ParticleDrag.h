#pragma once
#include "ParticleForceGenerator.h"
class ParticleDrag :
    public ParticleForceGenerator
{
private:
    //drag coefficients
    float m_k1, m_k2;

public:
    ParticleDrag(float k1, float k2) :m_k1{ k1 }, m_k2{ k2 } {};
    virtual void UpdateForce(Particle* particle, float deltaTime);

};

