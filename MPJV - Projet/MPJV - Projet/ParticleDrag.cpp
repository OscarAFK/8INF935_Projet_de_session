#include "ParticleDrag.h"

void ParticleDrag::UpdateForce(Particle* particle, float deltaTime)
{
	particle->addForce(-1*particle->getVelocity()*(m_k1* particle->getVelocity().normalize()+m_k2)* particle->getVelocity().normalize());
}
