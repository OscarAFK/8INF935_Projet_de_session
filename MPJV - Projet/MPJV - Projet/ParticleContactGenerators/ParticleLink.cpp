#include "ParticleLink.h"

ParticleLink::ParticleLink(Particle* p1, Particle* p2)
{
	m_particles[0] = p1;
	m_particles[1] = p2;
}

float ParticleLink::currentLength() const
{
	return (m_particles[0]->getPosition()- m_particles[1]->getPosition()).norm();
}
