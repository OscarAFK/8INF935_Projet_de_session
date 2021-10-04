#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private :
	Vector3D m_gravity;
public :
	ParticleGravity(Vector3D gravity = Vector3D(0, -10, 0)) : m_gravity{ gravity } {};
	void UpdateForce(Particle* particle, float duration);
	std::string to_string();
};