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
	ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity) : m_maxDepth{ maxDepth }, m_volume{ volume }, m_waterHeight{ waterHeight }, m_liquidDensity{ liquidDensity }  {};
	void UpdateForce(Particle* particle, float deltaTime);

};