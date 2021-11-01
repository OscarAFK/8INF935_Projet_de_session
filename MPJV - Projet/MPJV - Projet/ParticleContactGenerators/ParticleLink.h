#pragma once
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
public:

	//Linked particles
	Particle* m_particles[2];

	//Retunr th length of the link
	float currentLength() const;

	//Takes a pointer to an array of contact and the number of contact left to be generated
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) = 0;
};