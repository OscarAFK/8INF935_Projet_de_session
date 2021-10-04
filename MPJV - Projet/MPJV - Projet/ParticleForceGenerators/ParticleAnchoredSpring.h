#pragma once
#include "ParticleForceGenerator.h"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
	// other anchor
	Vector3D* m_other;

	// Spring constant
	float m_k;

	float m_restLength;

public:
	void UpdateForce(Particle* particle, float deltaTime);

};