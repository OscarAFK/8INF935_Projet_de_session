#include "ParticleRod.h"

unsigned int ParticleRod::addContact(std::vector<ParticleContact*>* contact, unsigned int limit) const
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

ParticleRod::ParticleRod(Particle* p1, Particle* p2, int length) : ParticleLink(p1,p2), m_length(length) {}