#pragma once
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	ParticleCable(Particle* p1, Particle* p2, float maxLength, float restitution);
	// A contact will be generated if the distance
	//between particles is larger than maxLength
	float m_maxLength;

	//bounciness of the cable
	float m_restitution;

	unsigned int addContact(std::vector<ParticleContact>* contact, unsigned int limit);

};