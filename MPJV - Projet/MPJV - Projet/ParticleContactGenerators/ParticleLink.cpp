#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	return (m_particles[0]->getPosition()- m_particles[1]->getPosition()).norm();
}
