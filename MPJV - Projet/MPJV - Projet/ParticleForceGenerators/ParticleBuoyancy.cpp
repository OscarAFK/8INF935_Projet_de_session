#include "ParticleBuoyancy.h"

void ParticleBuoyancy::UpdateForce(Particle* particle, float deltaTime)
{
	float d = (*particle->getPosition().getY() - m_waterHeight - m_maxDepth) / m_maxDepth;
	if (d <= 0) {
		return;
	}
	else if (d >= 1) {
		particle->addForce(m_liquidDensity * m_volume);
	}
	else {
		particle->addForce(m_liquidDensity * m_volume * d);
	}
}
