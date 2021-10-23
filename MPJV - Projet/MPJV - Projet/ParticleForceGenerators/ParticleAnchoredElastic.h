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
	ParticleAnchoredElastic(Vector3D* anchorPoint, float k, float restLength) : m_other{ anchorPoint }, m_k{ k }, m_restLength{ restLength }  {};
	void UpdateForce(Particle* particle, float deltaTime);

};