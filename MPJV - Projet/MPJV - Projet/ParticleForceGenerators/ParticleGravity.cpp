#include "ParticleGravity.h"

void ParticleGravity::UpdateForce(Particle* particle, float deltaTime)
{
	particle->addForce(m_gravity);
}
