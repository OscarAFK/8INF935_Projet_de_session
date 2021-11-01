#include "ParticleCable.h"
#include <iostream>

ParticleCable::ParticleCable(Particle* p1, Particle* p2, float maxLength, float restitution)
{
	m_particles[0] = p1;
	m_particles[1] = p2;
	m_maxLength = maxLength;
	m_restitution = restitution;
}
unsigned int ParticleCable::addContact(std::vector<ParticleContact>* contact, unsigned int limit)
{	
	if (currentLength() > m_maxLength) {
		contact->push_back(ParticleContact(m_particles[0], m_particles[1], 0, m_maxLength - currentLength()));
		return 1;
	}
	return 0;
}


