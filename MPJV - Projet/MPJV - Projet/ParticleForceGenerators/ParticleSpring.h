#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	// other particle anchor
	Particle* m_other;

	// Spring constant
	float m_k;

	float m_restLength;

public:
	ParticleSpring(Particle* anchorParticle, float k, float restLength) : m_other{ anchorParticle }, m_k{ k }, m_restLength{ restLength }  {};
	void UpdateForce(Particle* particle, float deltaTime);

};