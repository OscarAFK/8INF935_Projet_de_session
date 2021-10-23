#include "ParticleRod.h"

unsigned int ParticleRod::addContact(std::vector<ParticleContact*>* contact, unsigned int limit) 
{
	if (currentLength() < m_length) {
		contact->push_back(new ParticleContact(m_particles[0], m_particles[1] , 0, m_length - currentLength()));
		return 1;
	}else if (currentLength() > m_length) {
		contact->push_back(new ParticleContact(m_particles[0], m_particles[1], 0, currentLength()-m_length));
		return 1;
	}

	return 0;
}
