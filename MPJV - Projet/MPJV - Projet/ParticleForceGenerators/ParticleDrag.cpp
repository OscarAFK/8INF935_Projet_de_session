#include "ParticleDrag.h"

void ParticleDrag::UpdateForce(Particle* particle, float deltaTime)
{
	particle->addForce(Vector3D::vectProduct(-1 * particle->getVelocity().normalize(), m_k1 * particle->getVelocity().norm() + m_k2 * pow(particle->getVelocity().norm(), 2)));
}
