#include "ParticleSpring.h"

void ParticleSpring::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D d = m_other->getPosition()-particle->getPosition();
	particle->addForce(Vector3D::scalarProduct(-m_k*(d.norm()- m_restLength),d.normalize()));
}
