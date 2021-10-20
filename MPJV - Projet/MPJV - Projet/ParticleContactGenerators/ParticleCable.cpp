#include "ParticleCable.h"

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
	if (limit <= 0)
		return 1;

	if (currentLength() > m_maxLength) {
		contact = new ParticleContact(m_particles[0], m_particles[1], 0, currentLength() - m_maxLength);
	}

	return 0;
}
