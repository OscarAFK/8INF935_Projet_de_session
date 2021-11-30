#include "ParticleDrag.h"

void ParticleDrag::UpdateForce(Particle* particle, float deltaTime)
{
	particle->addForce(Vector3D::vectProduct(particle->getVelocity().normalize() * -1.0f, m_k1 * particle->getVelocity().norm() + m_k2 * pow(particle->getVelocity().norm(), 2)));
}
