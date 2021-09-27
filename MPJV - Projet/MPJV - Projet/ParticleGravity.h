#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private :
	Vector3D m_gravity;
public :
	//F = particle->GetMass()*m_gravity
	void UpdateForce(Particle* particle, float duration);
};