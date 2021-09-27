#pragma once
#include "ParticleForceGenerator.h"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
	// particle properties
	float m_maxDepth, m_volume;

	// effect properties
	float m_waterHeight, m_liquidDensity;

public:
	void UpdateForce(Particle* particle, float deltaTime);

};