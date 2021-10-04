#include "ParticleGravity.h"
#include <iostream>

void ParticleGravity::UpdateForce(Particle* particle, float deltaTime)
{
	std::cout << particle->to_string();
	//particle->addForce(particle->getMass() * m_gravity);
}

std::string ParticleGravity::to_string()
{
	return "Gravity Generator : " + m_gravity.to_string() + "\n";
}