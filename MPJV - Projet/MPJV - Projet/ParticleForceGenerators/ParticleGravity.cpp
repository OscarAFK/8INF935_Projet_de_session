#include "ParticleGravity.h"

void ParticleGravity::UpdateForce(Particle* particle, float deltaTime)
{
	particle->addForce(particle->getMass()*m_gravity);
}

std::string ParticleGravity::to_string()
{
	return "Gravity Generator : "+ m_gravity.to_string() + "\n";
}
