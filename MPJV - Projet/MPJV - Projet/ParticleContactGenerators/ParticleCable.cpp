#include "ParticleCable.h"

unsigned int ParticleCable::addContact(std::vector<ParticleContact*>* contact, unsigned int limit) const
{	
	if (currentLength() > m_maxLength) {
		contact->push_back(new ParticleContact(m_particles[0], m_particles[1], 0, currentLength() - m_maxLength));
		return 1;
	}
	return 0;
}
