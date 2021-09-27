#pragma once
#include "ParticleForceGenerator.h"
class ParticleAnchoredElastic :
    public ParticleForceGenerator
{
private:
	// other particle anchor
	Vector3D* m_other;

	// Spring constant
	float m_k;

	float m_restLength;

public:
	void UpdateForce(Particle* particle, float deltaTime);

};