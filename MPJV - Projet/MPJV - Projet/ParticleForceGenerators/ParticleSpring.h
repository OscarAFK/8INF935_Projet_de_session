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
	void UpdateForce(Particle* particle, float deltaTime);

};