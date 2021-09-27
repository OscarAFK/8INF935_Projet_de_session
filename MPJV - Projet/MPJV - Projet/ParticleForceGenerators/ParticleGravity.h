#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private :
	Vector3D m_gravity;
public :
	ParticleGravity(float gravity = -10) : m_gravity{ gravity } {};
	void UpdateForce(Particle* particle, float duration);
};