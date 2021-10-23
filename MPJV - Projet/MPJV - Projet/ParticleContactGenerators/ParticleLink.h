#pragma once
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
public:
	ParticleLink(Particle* p1, Particle* p2);

	//Linked particles
	Particle* m_particles[2];

	//Retunr th length of the link
	float currentLength() const;

	//Takes a pointer to an array of contact and the number of contact left to be generated
	virtual unsigned int addContact(std::vector<ParticleContact*>* contact, unsigned int limit) const = 0;
};