#include "ParticleAnchoredSpring.h"

void ParticleAnchoredSpring::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D d = *m_other - particle->getPosition();
	particle->addForce(Vector3D::scalarProduct(-m_k * (d.norm() - m_restLength), d.normalize()));
}
