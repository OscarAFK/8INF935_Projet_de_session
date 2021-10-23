#include "ParticleRod.h"

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) const
{
	if (limit <= 0)
		return 1;

	if (currentLength() < m_length) {
		contact = new ParticleContact(m_particles[0], m_particles[1] , 0, m_length - currentLength());

	}else if (currentLength() > m_length) {
		contact = new ParticleContact(m_particles[0], m_particles[1], 0, currentLength()-m_length);
	}

	return 0;
}
