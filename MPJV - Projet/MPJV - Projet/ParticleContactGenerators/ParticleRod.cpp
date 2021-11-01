#include "ParticleRod.h"

unsigned int ParticleRod::addContact(ParticleContact* contact, unsigned int limit) 
{
	if (limit >= 1) {
		if (currentLength() < m_length) {
			*contact = ParticleContact(m_particles[0], m_particles[1], 0, m_length - currentLength());
			return 1;
		}
		else if (currentLength() > m_length) {
			*contact = ParticleContact(m_particles[0], m_particles[1], 0, currentLength() - m_length);
			return 1;
		}
	}

	return 0;
}
