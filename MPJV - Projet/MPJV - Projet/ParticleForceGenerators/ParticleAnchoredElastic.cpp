#include "ParticleAnchoredElastic.h"

void ParticleAnchoredElastic::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D d = *m_other - particle->getPosition();
	if(d.norm()>m_k)
		particle->addForce(Vector3D::scalarProduct(-m_k * (d.norm() - m_k), d.normalize()));
}
